#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

// Function to check if a string represents a valid date-time format
bool isValidDateTime(const std::string& dateTime) {
    // Regular expression to match the format: d/m/yyyy hh:mm
    std::regex dateTimeRegex(R"(\d{1,2}/\d{1,2}/\d{4} \d{1,2}:\d{2})");
    return std::regex_match(dateTime, dateTimeRegex);
}

int main() {
    // Open input and output files
    std::ifstream inputFile("input.csv");
    std::ofstream outputFile("output.csv");

    // Check if files were opened successfully
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    std::string line;
    // Read and write the header line
    std::getline(inputFile, line);
    outputFile << line << std::endl;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;

        // Tokenize the line
        while (std::getline(iss, token, '\t')) {
            tokens.push_back(token);
        }

        // Assuming the start date and time are at specific columns (adjust as needed)
        std::string startDate = tokens[5];
        std::string startTime = tokens[6];

        // Check if the start time matches the required format
        if (isValidDateTime(startDate + " " + startTime)) {
            // Write the row to the output file
            outputFile << line << std::endl;
        }
    }

    // Close input and output files
    inputFile.close();
    outputFile.close();

    std::cout << "Filtering completed. Output written to output.csv" << std::endl;

    return 0;
}
