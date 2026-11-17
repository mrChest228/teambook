#include <bits/stdc++.h>
#include <thread>

#define f first
#define s second
#define pb push_back
#define in insert
#define elif else if
#define nl '\n'

#define  long  int64_t
#define ulong uint64_t

using namespace std;
namespace fs = filesystem;

void signalHandler(int signum) {
    exit(0);
}

//void help() {
//    cout << "It's a typst converter for team olimpiad docs." << nl
//         << "Run with argument <path> to convert file once." << nl
//         << "Run with arguments \"watch <path>\" to convert file on every change.";
//}

const fs::path src = "TeamBook.txt", dest = "TeamBook.typ";
// Goes before the first line, so line numbers in TeamBook.typ match TeamBook.txt
const string prefix = "#import \"default.typ\": *;#show: setup;";

void normalize(string &str) {
    // Remove the UTF-8 BOM, if it exists (0xEF 0xBB 0xBF)
    if (str.size() >= 3 &&
        static_cast<unsigned char>(str[0]) == 0xEF &&
        static_cast<unsigned char>(str[1]) == 0xBB &&
        static_cast<unsigned char>(str[2]) == 0xBF)
        str.erase(0, 3);
    if (str.back() != '\n')
        str.pb('\n');
}

vector <array <string, 4>> tokens = {
    {"$", "$", "$", "$"},                                  // Math
    {"```", "```", "```", "```"},                          // Code
    {"``", "``", "#code(\"", "\")"},                         // Inline code
    {"~~", "~~", "", ""},                                  // Typst functions
    {"_", "_", "#underline[", "]"},                        // Underline
    {"`", "`", "_", "_"},                                  // Italic
    {"*", "*", "*", "*"},                                  // Bold
    {"=== ", "\n", "=== ", "#br\n"},
    {"== ", "\n", "== ", "#br\n"},
    {"= ", "\n", "= ", "#br\n"}
};

const int inlineCode = 2;   // Index of the inline code in tokens
const int firstHeading = 7; // Index of the first heading in tokens

// Escapes text for a Typst string literal
string escape(const string &str) {
    string ans;
    for (char c : str) {
        if (c == '\\' || c == '"')
            ans.pb('\\');
        ans.pb(c);
    }
    return ans;
}

string normalSpaces(const string str) {
    string ans;
    for (char c : str) {
        if ((c == ' ' || c == '\n') != (ans.size() && (ans.back() == ' ' || ans.back() == '\n')))
            ans.pb('`');
        ans.pb(c);
    }
    if (ans.size() && (ans.back() == ' ' || ans.back() == '\n'))
        ans.pb('`');
    return ans;
}

string solve(const string &text, int l, int r) {
    if (l == r)
        return "";
    for (int i = l; i < r; ++i)
        for (int j = 0; j < tokens.size(); ++j)
            if (i + tokens[j][0].size() <= r && text.substr(i, tokens[j][0].size()) == tokens[j][0] &&
                (j < firstHeading || i == 0 || text[i - 1] == '\n')) { // Headings start a line
                int k = i + tokens[j][0].size();
                while (k + tokens[j][1].size() <= r && text.substr(k, tokens[j][1].size()) != tokens[j][1])
                    ++k;
                if (k + tokens[j][1].size() > r)
                    throw "Line " + to_string(count(text.begin(), text.begin() + i, '\n') + 1) +
                          ": bad count of token \"" + tokens[j][0] + "..." + tokens[j][1] + "\"";
                string pref, open = tokens[j][2], close = tokens[j][3];
                if (j >= firstHeading) {
                    if (i == 0) { // Typst sees no "=" after the prefix in the first line
                        open = "#heading(depth: " + to_string(tokens[j][0].size() - 1) + ")[";
                        close = "]#br\n";
                    }
                    elif (i > l) // The "=" has to start a line in TeamBook.typ too
                        pref = normalSpaces(text.substr(l, i - 1 - l)) + "#br\n";
                }
                elif (i > l)
                    pref = normalSpaces(text.substr(l, i - l));
                string inner;
                if (j > 3)
                    inner = solve(text, i + tokens[j][0].size(), k);
                else
                    inner = text.substr(i + tokens[j][0].size(), k - (i + tokens[j][0].size()));
                if (j == inlineCode)
                    inner = escape(inner);
                return pref +
                       open + inner + close +
                       solve(text, k + tokens[j][1].size(), r);
            }
    return normalSpaces(text.substr(l, r - l));
}

void convert() {
    // Reading
    ifstream in(src, ios::binary);
    if (!in) {
        cerr << "[convert] cannot open source for reading: " << src << "\n";
        return;
    }
    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    normalize(text);

    string res = prefix;

    try {
        res += solve(text, 0, text.size());
    }
    catch (string err) {
        cerr << "[convert] " << err << nl;
        return;
    }
    // Drop the line break made by the final newline
    if (res.ends_with("#br\n"))
        res.erase(res.size() - 4);
    else
        res.erase(----res.end());

    // Writing
    ofstream out(dest, ios::binary);
    if (!out) {
        cerr << "[convert] cannot open dest for writing: " << dest << "\n";
        return;
    }
    out.write(res.data(), static_cast<streamsize>(res.size()));
    out.close();
}

void watch() {
    chrono::file_clock::time_point lastTime;
    int isFound = -1;
    while (1) {
        this_thread::sleep_for(700ms);
        error_code ec;
        if (!fs::exists(src, ec)) {
            if (ec)
                cerr << "[watch] filesystem error checking existence: " << ec.message() << nl;
            if (isFound != 0)
                cout << "File " << src << " didn't found\n";
            isFound = 0;
            continue;
        }
        isFound = 1;
        auto curTime = fs::last_write_time(src, ec);
        if (ec) {
            cerr << "[watch] error reading timestamp: " << ec.message() << nl;
            continue;
        }
        if (curTime != lastTime) {
            cout << "Changes have been detected\n";
            lastTime = curTime;
            auto startTime = chrono::high_resolution_clock::now();

            convert();

            auto endTime = chrono::high_resolution_clock::now();
            double dur = (chrono::duration<double, milli>(endTime - startTime)).count();

            cout << "Time: " << dur << "ms.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    // Ctrl-C handling
    signal(SIGINT, signalHandler);

    watch();

    return 0;
}
