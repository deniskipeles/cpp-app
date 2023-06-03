#include <iostream>
#include <string>
#include "html2text.h"

int main() {
    // Sample HTML input
    std::string html = "<html><body><h1>Hello, World!</h1><p>This is an example HTML document.</p></body></html>";

    // Create an instance of HTML2Text
    HTML2Text converter;

    // Convert the HTML to plain text
    std::string text = converter.convert(html);

    // Print the plain text
    std::cout << "Plain Text:\n" << text << std::endl;

    return 0;
}
