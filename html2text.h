#ifndef HTML2TEXT_H
#define HTML2TEXT_H

#include <string>

class HTML2Text {
public:
    // Constructor
    HTML2Text();

    // Destructor
    ~HTML2Text();

    // Convert HTML to plain text
    std::string convertToPlainText(const std::string& html);
};

#endif // HTML2TEXT_H
