#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include "Huffman.h"

struct Node {
    unsigned char value;
    int freq;
    struct Node *left = nullptr;
    struct Node *right = nullptr;

    Node(unsigned char c, int f, Node* l, Node* r) {
        value = c;
        freq = f;
        left = l;
        right = r;
    }

};
struct CmpNode
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        return (lhs.freq < rhs.freq);
    }
};
class Huffman {
public:
    std::vector<bool> encode(std::vector<unsigned char>);
    std::vector<unsigned char> decode(std::vector<bool> v);

private:
    std::map<unsigned char,std::vector<bool> > char2boolv;

    Node root = {'-', 0, nullptr, nullptr};
    void make_char2boolv();
};
void Huffman::make_char2boolv() {
    std::vector<bool> cur;

    std::stack<std::pair<Node, std::vector<bool> > > s;
    s.push(std::make_pair(root, std::vector<bool>()));
    while (!s.empty()) {
        Node t = s.top().first;
        std::vector<bool> t_b = s.top().second;
        s.pop();
        if (!t.right && !t.left) {
            char2boolv[t.value] = t_b;
        }
        if (t.right) {
            t_b.push_back(true);
            s.push(std::make_pair(*t.right, t_b));
        }
        t_b.pop_back();
        if (t.left) {
            t_b.push_back(false);
            s.push(std::make_pair(*t.left, t_b));
        }
    }
}
std::vector<bool> Huffman::encode(std::vector<unsigned char> const s) {
    std::map<unsigned char, int> freq;
    for (auto& c : s)
        freq[c] += 1;

    std::multiset<Node, CmpNode> freq_set;
    for (auto& elem : freq){
        auto first = elem.first;
        auto second = elem.second;
        Node n = {first, second, nullptr, nullptr};
        freq_set.insert(n);
    }
    while (freq_set.size() > 1) {
        Node fs = *freq_set.begin();
        freq_set.erase(freq_set.begin());
        Node sc = *freq_set.begin();
        freq_set.erase(freq_set.begin());

        Node n = {'-', fs.freq + sc.freq, nullptr, nullptr};

        n.left = new Node(fs.value, fs.freq, fs.left, fs.right);
        n.right = new Node(sc.value, sc.freq, sc.left, sc.right);

        freq_set.insert(n);
    }

    Node r = *freq_set.begin();
    root.value = r.value;
    root.freq = r.freq;
    root.left = r.left;
    root.right = r.right;

    make_char2boolv();

    std::vector<bool> result;
    for (auto el: s) {
        for (auto b: char2boolv[el]) {
            result.push_back(b);
        }
    }

    return result;
}
std::vector<unsigned char> Huffman::decode(std::vector<bool> v) {
    std::vector<unsigned char> result;
    Node cur = root;
    int i = 0;
    while (i != v.size()) {
        if (v[i] == 0) {
            cur = *cur.left;
        } else {
            cur = *cur.right;
        }
        if (!cur.right && !cur.left) {
            result.push_back(cur.value);
            cur = root;
        }
        i += 1;
    }
    return result;
}

class BitsWriter {
public:
    void WriteBit(bool bit);
    void WriteByte(byte byte);

    std::vector<byte> GetResult();

private:
    std::vector<byte> buffer_;
    byte accumulator_ = 0;
    int bits_count_ = 0;
};
void BitsWriter::WriteBit(bool bit) {
    // Ставим бит в аккумулятор на нужное место
    accumulator_ |= static_cast<byte>(bit) << bits_count_;
    ++bits_count_;
    if (bits_count_ == 8) {
        bits_count_ = 0;
        buffer_.push_back(accumulator_);
        accumulator_ = 0;
    }
}
void BitsWriter::WriteByte(byte byte) {
    if (bits_count_ == 0) {
        buffer_.push_back(byte);
    } else {
        accumulator_ |= byte << bits_count_;
        buffer_.push_back(accumulator_);
        accumulator_ = byte >> (8 - bits_count_);
    }
}
std::vector<byte> BitsWriter::GetResult() {
    if (bits_count_ != 0) {
        // Добавляем в буфер аккумулятор, если в нем что-то есть.
        buffer_.push_back(accumulator_);
    }
    buffer_.push_back(static_cast<byte>(bits_count_));
    return std::move(buffer_)
void Encode(IInputStream& original, IOutputStream& compressed){
    byte value;
    vector<byte> inp;
    while (original.Read(value)){
        inp.push_back(value);
    }
    Huffman h;
    auto inp_enc = h.encode(inp);

    BitsWriter bits_writer;
    for (auto b: inp_enc) {
        bits_writer.WriteBit(b);
    }

    std::vector<byte> result = std::move(bits_writer.GetResult());

    for (auto b : result) {
        compressed.Write(b);
    }
}


std::vector <bool> ReadAll(std::vector<byte> enc){
    byte byte = enc[enc.size()-1];
    int present = ((byte >> 0) & 1) + 2 * ((byte >> 1) & 1) + 4 * ((byte >> 2) & 1);
    int to_del = (8 - present) % 8;

    std::vector<bool> res;
    for (int byte_i = 0; byte_i < enc.size() - 1; byte_i++) {
        int byte_len = 8;
        if (enc.size()-2 == byte_i)
            byte_len -= to_del;
        for (int i = 0; i < byte_len; i++) {
            res.push_back((enc[byte_i] >> i) & 1);
        }
    }

    return res;
}
void Decode(IInputStream& compressed, IOutputStream& original){
    byte value;
    vector<byte> inp;
    while (compressed.Read(value)){
        inp.push_back(value);
    }

    for (auto b: inp) {
        original.Write(b);
    }
}
