#include "huffmanSystem.h"
#include <windows.h>
#include <filesystem>
#include <vector>
#include <iomanip>
using namespace std;
namespace fs = std::filesystem;

double calc_compression_ratio(const string& src, const string& huff) {
    ifstream srcf(src, ios::binary | ios::ate);
    ifstream hufff(huff, ios::binary | ios::ate);
    if (!srcf.is_open() || !hufff.is_open()) return -1.0;
    auto src_size = srcf.tellg();
    auto huff_size = hufff.tellg();
    if (src_size == 0) return -1.0;
    return double(huff_size) / double(src_size);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<pair<string, string>> samples = {
        {"hamlet.txt", "hamlet.huff"},
        {"mit.txt", "mit.huff"},
        {"logo_bmp.bmp", "logo_bmp.huff"},
        {"logo_png.png", "logo_png.huff"},
        {"mv.mp4", "mv.huff"},
        {"pdf.pdf", "pdf.huff"},
        {"srcode.h", "srcode.huff"}
    };
    string test_dir = "./";
    cout << left << setw(18) << "样例文件" << setw(25) << "原文件大小" << setw(22) << "压缩后大小" << setw(23) << "压缩率" << endl;
    for (auto& [src, huff] : samples) {
        string src_path = test_dir + src;
        string huff_path = test_dir + huff;
        ifstream srcf(src_path, ios::binary | ios::ate);
        ifstream hufff(huff_path, ios::binary | ios::ate);
        if (!srcf.is_open() || !hufff.is_open()) {
            cout << left << setw(18) << src << "文件缺失，跳过" << endl;
            continue;
        }
        auto src_size = srcf.tellg();
        auto huff_size = hufff.tellg();
        double ratio = src_size == 0 ? 0.0 : double(huff_size) / double(src_size);
        cout << left << setw(18) << src << setw(15) << src_size << setw(15) << huff_size << fixed << setprecision(4) << ratio << endl;
    }

    HuffmanSystem hfm = HuffmanSystem();
    hfm.run();
    
    return 0;
}