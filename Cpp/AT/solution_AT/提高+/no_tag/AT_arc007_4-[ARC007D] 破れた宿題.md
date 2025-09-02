# [ARC007D] 破れた宿題

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc007/tasks/arc007_4

 高橋君は数学の宿題で出された、等差数列の初項と公差を答える問題を解いています。  
 隣接する $ 2 $ つの数字間の差が定数である数字の連続のことを等差数列といい、最初の数字を初項、定数である数字間の差を公差、最後の数字を末項と呼びます。  
 ただ高橋君はうっかり宿題の数列を空白やカンマで区切ることなく $ 0 $から $ 9 $ の数字で構成された $ 1 $ つの文字列としてノートに写しとってしまいました。  
 さらにそのノートの扱いが雑だったので、ノートの一部を破って切り離してしまいました。  
 破れて切り離されてしまったのは初項と末項の部分だけで、少なくとも初項の一部分が残っているのを確認しました。  
 そのような文字列が与えられるので、元の数列を推測してその初項と公差を答えなさい。  
  
 なお、初項と公差は $ 1 $ 以上の整数であり、解が複数ある場合は初項が最も小さいものを答え、初項が等しい解が複数ある場合は公差が最も小さいものを答えなさい。  
 また、$ 003 $ や $ 012 $ のように不必要な $ 0 $ が前に付属している数字は写しとった数列には含まれていませんでした。 入力は以下の形式で標準入力から与えられる。

> $ c_{0} $$ c_{1} $‥‥$ c_{N-1} $

- 入力は $ 1 $ 行のみで等差数列の一部である長さ $ N $ の文字列が与えられる。
- 文字列は `0-9` から成り立っている。
 
 テストデータには以下の $ 4 $ 種類のテストデータセットのいずれかに含まれており、それぞれのデータセットに含まれているテストデータは以下に示すように与えられる文字列 $ N $ の範囲が異なっている。  
 あるテストデータセットに含まれているテストデータ全てに対して正しい解を出力できると、それ以外のテストデータセットで不正解を出力しても以下のように部分点が与えられる。  
- level1 ( $ 25 $ 点) : $ 1≦N≦4 $
- level2 ( $ 25 $ 点) : $ 1≦N≦6 $
- level3 ( $ 25 $ 点) : $ 1≦N≦200 $
- level4 ( $ 25 $ 点) : $ 1≦N≦1,000 $
 
 初項と末項の一部が切り離されている可能性のある等差数列に対して考えうる初項と公差を空白区切りで標準出力に $ 1 $ 行で出力せよ。  
 解が複数ある場合は初項が最も小さいものを答え、初項が等しい解が複数ある場合は公差が最も小さいものを出力せよ。  
 なお、最後には改行を出力せよ。 ```

1
```

 ```

1 1
```

- 前後に文字が続く $ 1 $ つの数字の可能性もありますが、最も小さい初項は数字が切り離されていない場合の $ 1 $ です。
- 公差も任意の正の整数が考えられますが、最も小さい公差は $ 1 $ です。
 
```

0203
```

 ```

10 10
```

- $ 02 $ は数字として認められないので $ 2 $ は初項ではありません。
- 初項の $ 10 $ の $ 1 $ が切り離されており、末項として $ 30 $ の $ 0 $ が切り離された数列であり、元の数列は `102030`です。
 
```

456789101112131415
```

 ```

4 1
```

- 数列のどこも欠けていない初項 $ 4 $、公差 $ 1 $ の等差数列です。
 
```

579111315171921232
```

 ```

5 2
```

- 末項の $ 25 $ の $ 5 $ の部分が欠けている等差数列です。
 
```

001131261391521651
```

 ```

100 13
```

- 初項の $ 100 $ と末項の $ 178 $ の一部が欠けています。

# 题解

## 作者：Y204335 (赞：1)

# \[ARC007D] 破れた宿題

## 题目大意

给定字符串 $s$，其为一个无前导零的等差数列在首尾项分别缺失前后缀（不完全缺失）后，每个数字头尾相连得到，问所有可能的原始等差数列中首项最小的等差数列（有多个输出公差最小的）的首项和公差。

## 题目分析

由于要求首项最小，所以可以将第一个数字以及之后一段连续的零作为首项，当第一个数字为零时，在前面加一个一即可，由于该等差数列可以只有两项，所以这一定是有解的。

然后枚举第二项的长度，暴力检验之后的项是否合法，取第一种合法的情况即可。

由于数字很大，需要写高精度，代码中的高精度实现不是很好，但能用。

实现的细节有点多，要注意公差不能为零，在只有两项时需要通过在尾项后补零来处理，当第一项的长度为总长时需要特判（后面全是零时）。

时间复杂度 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define out()     \
    {             \
        flag = 0; \
        break;    \
    }
using namespace std;
int n, len, nw;
bool flag;
string s, fir, diff, sec, nxt;
string operator+(string a, string b)
{
    string res;
    int nxt = 0;
    if (a.size() > b.size())
        swap(a, b);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < (int)a.size(); i++) {
        res += (char)((nxt + a[i] - '0' + b[i] - '0') % 10 + '0');
        nxt = (nxt + a[i] - '0' + b[i] - '0') / 10;
    }
    for (int i = a.size(); i < (int)b.size(); i++) {
        res += (char)((nxt + b[i] - '0') % 10 + '0');
        nxt = (nxt + b[i] - '0') / 10;
    }
    if (nxt)
        res += (char)(nxt + '0');
    reverse(res.begin(), res.end());
    return res;
}
bool operator<(string a, string b)
{
    if (a.size() < b.size())
        return 1;
    if (a.size() > b.size())
        return 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] < b[i])
            return 1;
        else if (a[i] > b[i])
            return 0;
    }
    return 0;
}
bool operator<=(string a, string b)
{
    if (a.size() < b.size())
        return 1;
    if (a.size() > b.size())
        return 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] < b[i])
            return 1;
        else if (a[i] > b[i])
            return 0;
    }
    return 1;
}
string operator-(string a, string b)
{
    string res;
    int nxt = 0;
    if (a < b)
        return "0";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < (int)b.size(); i++) {
        int temp = a[i] - b[i] + nxt;
        if (temp < 0) {
            temp += 10;
            nxt = -1;
        } else
            nxt = 0;
        res += (char)(temp + '0');
    }
    for (int i = b.size(); i < (int)a.size(); i++) {
        int temp = a[i] - '0' + nxt;
        if (temp < 0) {
            temp += 10;
            nxt = -1;
        } else
            nxt = 0;
        res += (char)(temp + '0');
    }
    while (res.back() == '0')
        res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    n = s.size();
    s = '#' + s;
    if (s[1] == '0') {
        fir = "1";
        for (int i = 1; i <= n && s[i] == '0'; i++) {
            len = i;
            fir += '0';
        }
    } else {
        fir = s[1];
        len = 1;
        for (int i = 2; i <= n && s[i] == '0'; i++) {
            len = i;
            fir += '0';
        }
    }
    if (len == n) {
        cout << fir << ' ' << 1 << '\n';
        return 0;
    }
    for (int i = len + 1; i <= n; i++) {
        sec += s[i];
        if (sec <= fir)
            continue;
        diff = sec - fir;
        nw = i + 1;
        nxt = sec;
        flag = 1;
        while (nw <= n) {
            nxt = nxt + diff;
            for (int j = nw; j <= min(nw + (int)nxt.size() - 1, n); j++) {
                if (s[j] != nxt[j - nw])
                    out();
            }
            nw += nxt.size();
        }
        if (flag) {
            cout << fir << ' ' << diff << '\n';
            return 0;
        }
    }
    while (sec < fir || (sec == fir && (int)sec.size() == n - len))
        sec += '0';
    if (sec == fir) {
        cout << fir << ' ' << 1 << '\n';
        return 0;
    }
    cout << fir << ' ' << sec - fir << '\n';
    return 0;
}
```

---

