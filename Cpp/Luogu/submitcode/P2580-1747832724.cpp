#include<bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5; // 数组大小
int n, q;
int ch[maxn][27]; // 第二维开到 27，确保足够
int y[maxn], z[maxn]; // y 记录是否是一个名字的结尾，z 记录是否被查询过
int idx = 1; // Trie 节点编号
string s;

// 插入名字到 Trie 中
void insert(string x) {
    int p = 1; // 根节点
    for (int i = 0; i < x.size(); i++) {
        int j = x[i] - 'a'; // 计算字符对应的索引
        if (!ch[p][j]) {
            ch[p][j] = ++idx; // 创建新节点
        }
        p = ch[p][j]; // 移动到下一个节点
    }
    y[p] = 1; // 标记这是一个名字的结尾
}

// 查询名字
int query(string x) {
    int p = 1; // 根节点
    for (int i = 0; i < x.size(); i++) {
        int j = x[i] - 'a'; // 计算字符对应的索引
        if (!ch[p][j]) {
            return 0; // 名字不存在
        }
        p = ch[p][j]; // 移动到下一个节点
    }
    if (y[p]) { // 如果是一个名字的结尾
        if (z[p]) { // 如果已经被查询过
            return 2;
        } else {
            z[p] = 1; // 标记为已查询
            return 1;
        }
    }
    return 0; // 名字不存在
}

int main() {
    ios::sync_with_stdio(false); // 加速输入输出
    cin.tie(nullptr);

    // 初始化数组
    memset(ch, 0, sizeof(ch));
    memset(y, 0, sizeof(y));
    memset(z, 0, sizeof(z));

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        insert(s); // 插入名字
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> s;
        int num = query(s); // 查询名字
        if (num == 0) {
            cout << "WRONG" << endl;
        } else if (num == 1) {
            cout << "OK" << endl;
        } else {
            cout << "REPEAT" << endl;
        }
    }

    return 0;
}
