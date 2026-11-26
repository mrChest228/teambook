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

void normalize(string &str) {
    // Remove the UTF-8 BOM, if it exists (0xEF 0xBB 0xBF)
    if (str.size() >= 3 &&
        static_cast<unsigned char>(str[0]) == 0xEF &&
        static_cast<unsigned char>(str[1]) == 0xBB &&
        static_cast<unsigned char>(str[2]) == 0xBF)
        str.erase(0, 3);
    if (!str.empty() && str.back() != '\n')
        str.pb('\n');
}

vector <array <string, 4>> tokens = {
    {"$", "$", "$", "$"},                                  // Math
    {"```", "```", "```", "```"},                          // Code
    {"``", "``", "#code(\"", "\")"},                       // Inline code
    {"~~", "~~", "", ""},                                  // Typst functions
    {"_", "_", "#underline[", "]"},                        // Underline
    {"`", "`", "_", "_"},                                  // Italic
    {"*", "*", "*", "*"},                                  // Bold
    {"=== ", "\n", "=== ", "#br\n"},
    {"== ", "\n", "== ", "#br\n"},
    {"= ", "\n", "= ", "#br\n"}
};

const int inlineCode = 2;   // Index of the inline code in tokens
const int typstFun = 3;     // Index of Typst functions in tokens
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
                    throw to_string(count(text.begin(), text.begin() + i, '\n') + 1) +
                          ": bad count of token \"" + tokens[j][0] + "..." + tokens[j][1] + "\"";
                string pref;
                if (j >= firstHeading && i > l) // The "=" has to start a line in TeamBook.typ too
                    pref = normalSpaces(text.substr(l, i - 1 - l)) + "#br\n";
                elif (i > l)
                    pref = normalSpaces(text.substr(l, i - l));
                string inner;
                if (j > 3)
                    inner = solve(text, i + tokens[j][0].size(), k);
                else
                    inner = text.substr(i + tokens[j][0].size(), k - (i + tokens[j][0].size()));
                if (j == inlineCode)
                    inner = escape(inner);
                string open = tokens[j][2], close = tokens[j][3];
                if (j >= firstHeading && i == 0) {
                    open = "#heading(depth: " + to_string(10 - j) + ")[";
                    close = "]";
                }
                int next = k + tokens[j][1].size();
                if (j >= firstHeading && i == 0 && k < r && text[k] == '\n')
                    return pref + open + inner + close + "\n" + solve(text, next, r);
                if (j == typstFun && next < r && text[next] == '\n') {
                    if (inner.starts_with("#show:"))
                        return pref + open + inner + close + "\n" + solve(text, next + 1, r);
                    if (inner.starts_with("#include "))
                        return pref + open + inner + close + "\n#br\n" + solve(text, next + 1, r);
                }
                return pref +
                       open + inner + close +
                       solve(text, next, r);
            }
    return normalSpaces(text.substr(l, r - l));
}

void convert(const fs::path &src) {
    fs::path dest = fs::path("typ") / src.filename();
    dest.replace_extension(".typ");
    error_code dirEc;
    fs::create_directories(dest.parent_path(), dirEc);
    if (dirEc) {
        cerr << "[convert] cannot create destination directory: " << dest.parent_path() << ": " << dirEc.message() << nl;
        return;
    }
    // Reading
    ifstream in(src, ios::binary);
    if (!in) {
        cerr << "[convert] cannot open source for reading: " << src << "\n";
        return;
    }
    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    normalize(text);

    string res;

    try {
        res = solve(text, 0, text.size());
    }
    catch (string err) {
        cerr << src.generic_string() << ":" << err << nl;
        return;
    }
    // Drop the line break made by the final newline
    if (!res.empty()) {
        if (res.ends_with("#br\n"))
            res.erase(res.size() - 4);
        elif (res.ends_with('\n'))
            res.pop_back();
        else
            res.erase(----res.end());
    }
    res = "#import \"../book/default.typ\": *;" + res;

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
    while (1) {
        this_thread::sleep_for(700ms);
        fs::path dir = "book";
        error_code dirEc;
        if (!fs::is_directory(dir, dirEc)) {
            if (dirEc)
                cerr << "[watch] filesystem error checking " << dir << ": " << dirEc.message() << nl;
            else
                cerr << "[watch] directory not found: " << dir << nl;
            continue;
        }
        static map <fs::path, fs::file_time_type> lastTime;
        fs::directory_iterator it(dir, dirEc), end;
        if (dirEc) {
            cerr << "[watch] error reading " << dir << ": " << dirEc.message() << nl;
            continue;
        }
        while (it != end) {
            fs::path src = it->path();
            if (src.extension() == ".txt") {
                error_code timeEc;
                auto curTime = fs::last_write_time(src, timeEc);
                if (timeEc)
                    cerr << "[watch] error reading timestamp for " << src << ": " << timeEc.message() << nl;
                else {
                    auto seen = lastTime.find(src);
                    if (seen == lastTime.end() || seen->second != curTime) {
                        lastTime[src] = curTime;
                        cout << "Changes have been detected in " << src.generic_string() << nl;
                        auto start = chrono::steady_clock::now();
                        convert(src);
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(
                            chrono::steady_clock::now() - start
                        ).count();
                        cout << "Time: " << elapsed << "ms." << nl;
                    }
                }
            }
            it.increment(dirEc);
            if (dirEc) {
                cerr << "[watch] error reading " << dir << ": " << dirEc.message() << nl;
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Ctrl-C handling
    signal(SIGINT, signalHandler);

    watch();

    return 0;
}
