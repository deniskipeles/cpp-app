#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <nlp/TextRank.h>
#include <html2text/html2text.h>
#include <crow.h>

using namespace std;

// RequestBody represents the JSON payload for text summarization request.
struct RequestBody {
    string text;
};

// ResponseBody represents the JSON response containing the summarized text.
struct ResponseBody {
    string summary;
};

// summarizeText performs text summarization using the TextRank algorithm.
string summarizeText(const string& text) {
    // Convert HTML to plain text
    string plainText = html2text::convert(text);

    // Tokenize the text
    vector<string> sentences;
    istringstream iss(plainText);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(sentences));

    // Build a TextRank model
    nlp::TextRank model;

    // Add the sentences to the model
    for (const string& sentence : sentences) {
        model.addSentence(sentence);
    }

    // Calculate the TextRank scores
    model.rank();

    // Get the top-ranked sentences
    vector<nlp::Sentence> topSentences = model.getTopRankedSentences(5); // Adjust the number of sentences as needed

    // Combine the top sentences to form the summary
    vector<string> summarySentences;
    transform(topSentences.begin(), topSentences.end(), back_inserter(summarySentences),
              [](const nlp::Sentence& sentence) { return sentence.getValue(); });
    string summary = accumulate(summarySentences.begin(), summarySentences.end(), string(""));

    return summary;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/summary")
    .methods("POST"_method)
    ([](const crow::request& req, crow::response& res) {
        // Parse the request body
        RequestBody reqBody;
        try {
            reqBody = crow::json::load(req.body);
        } catch (const exception& e) {
            res.code = 400; // Bad Request
            res.end();
            return;
        }

        // Summarize the text
        string summary = summarizeText(reqBody.text);

        // Create the response body
        ResponseBody resBody;
        resBody.summary = summary;

        // Send the response
        res.set_header("Content-Type", "application/json");
        res.write(crow::json::dump(resBody));
        res.end();
    });

    cout << "Server started on http://localhost:8080" << endl;
    app.port(8080).multithreaded().run();

    return 0;
}
