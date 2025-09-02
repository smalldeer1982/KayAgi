# The Errant Physicist

## 题目描述

著名物理学家阿尔弗雷德·E·纽曼正在研究涉及多项式乘法的问题。例如，他可能需要计算
$$
(-x^8y+9x^3-1+y) \cdot (x^5y+1+x^3)
$$
得到答案
$$
-x^{13}y^2-x^{11}y+8x^8y+9x^6-x^5y+x^5y^2+8x^3+x^3y-1+y
$$
不幸的是，这些问题太微不足道了，以至于这位伟人的思绪总是游离在工作之外，他得到了错误的答案。因此，他设计的几枚核弹头过早引爆，摧毁了五个主要城市和几片雨林。
你要写一个程序来执行这样的乘法并拯救世界。

## 样例 #1

### 输入

```
-yx8+9x3-1+y
x5y+1+x3
1
1
#```

### 输出

```
13 2 11
8
6 5
5 2
3 3
-x y - x y + 8x y + 9x - x y + x y + 8x + x y - 1 + y
1```

# 题解

## 作者：XCD_OIworld_rookie (赞：6)

```cpp
#include<bits/stdc++.h>
using namespace std;
//表示多项式中各项的结构体
struct TERM {
    //成员分别为系数，x指数和y指数
    int cof; int xe; int ye;
    //构造函数，按参数初始化变量
    TERM (int c, int x, int y) : cof(c), xe(x), ye(y) {}
};
//比较两项指数的大小，用于排序和合并同类项
bool GreaterTerm(const TERM &t1, const TERM &t2) {
    return (t1.xe > t2.xe || (t1.xe == t2.xe && t1.ye < t2.ye));
}
//解析输入多项式字符串的函数
void ParsePolynomial(char *pStr, vector<TERM> &Terms) {
    //循环处理每一项
    for (int nNum; *pStr != 0;) {
        //确定该项的正负号，并初始化项结构体
        TERM Term(*pStr == '-' ? -1 : 1, 0, 0);
        //如果前面有符号，则指针向后移位
        pStr += (*pStr == '-' || *pStr == '+') ? 1 : 0;
        //如果系数为0，则跳过整项
        if (*pStr == '0') {
            for(++pStr; *pStr != '\0' && *pStr != '+' && *pStr != '-'; ++pStr);
            continue;
        }
        //读取符号后面的系数
        for (nNum = 0; isdigit(*pStr); nNum = nNum * 10 + *pStr++ - '0');
        //如果系数不为0，则乘到项结构体的系数中去(保留原符号)
        for (Term.cof *= (nNum == 0) ? 1 : nNum; isalpha(*pStr);) {
            //循环读取两个变量的指针(如果存在)，先确定是x还是y的指数
            int *pe = (*pStr == 'x') ? &Term.xe : &Term.ye;
            //读取后面的指数
            for (; isdigit(*++pStr); *pe = *pe * 10 + *pStr - '0');
            //没有指数即指数为1
            *pe = (*pe == 0) ? 1 : *pe;
        }
        //将新项结构体加入数组
        Terms.push_back(Term);
    }
}
//主函数
int main(void) {
    //循环读入所有输入的数据，遇到#号结束
    for (string str1, str2; cin >> str1 && str1 != "#"; ) {
        cin >> str2;
        if (str1.empty() || str2.empty()) continue;
        const int nMaxLen = 100;
        char szBuf1[nMaxLen], szBuf2[nMaxLen];
        vector<TERM> Poly1, Poly2, Result;
        //转存两个字符串以备解析多项式
        strcpy(szBuf1, str1.c_str());
        strcpy(szBuf2, str2.c_str());
        //解析两个多项式字符串
        ParsePolynomial(szBuf1, Poly1);
        ParsePolynomial(szBuf2, Poly2);
        vector<TERM>::iterator i, j;
        //执行多项式乘法
        for (i = Poly1.begin(); i != Poly1.end(); ++i) {
            for (j = Poly2.begin(); j != Poly2.end(); ++j) {
                TERM Term(i->cof * j->cof, i->xe + j->xe, i->ye + j->ye);
                Result.push_back(Term);
            }
        }
        //按项指数排序
        sort(Result.begin(), Result.end(), GreaterTerm);
        fill(&szBuf1[0], &szBuf1[nMaxLen], ' ');
        fill(&szBuf2[0], &szBuf2[nMaxLen], ' ');
        int nPos = 0;
        //查找同类项
        for (i = Result.begin(); i != Result.end(); ++i) {
            //合并后面的同类项(如果存在)
            for (j = i + 1; j < Result.end() &&
                i->xe == j->xe && i->ye == j->ye;) {
                i->cof += j->cof;
                j = Result.erase(j);
            }
            //如果该项的系数不为0，则将其输出
            if (i->cof != 0) {
                if (nPos > 0) { //不是第一项，输出中间的运算符
                    ++nPos; //输出运算符前面的空格
                    szBuf2[nPos++] = i->cof > 0 ? '+' : '-';
                    szBuf2[nPos++] = ' ';
                }
                else { //第一项，输出前面的符号(如果为负)
                    szBuf2[0] = '-';
                    nPos += (i->cof < 0);
                }
                //如果系数(绝对值)不为1或xy指数都为0，则输出系数
                i->cof = abs(i->cof);
                if (i->cof != 1 || (i->xe == 0 && i->ye == 0)) {
                    nPos += sprintf(&szBuf2[nPos], "%d", i->cof);
                    //给sprintf擦屁股
                    szBuf2[nPos] = ' ';
                }
                //如果x指数不为0，则输出x
                if (i->xe > 0) {
                    szBuf2[nPos++] = 'x';
                    if (i->xe > 1) {
                        nPos += sprintf(&szBuf1[nPos], "%d", i->xe);
                        szBuf1[nPos] = ' ';
                    }
                } //同上
                if (i->ye > 0) {
                    szBuf2[nPos++] = 'y';
                    if (i->ye > 1) {
                        nPos += sprintf(&szBuf1[nPos], "%d", i->ye);
                        szBuf1[nPos] = ' ';
                    }
                }
            }
        }
        //如果没有输出任何项，则多项式乘积为0
        if (nPos == 0) {
            szBuf2[nPos++] = '0';
        }
        //为多项式乘积字符串划结束符并输出
        szBuf1[nPos] = szBuf2[nPos] = '\0';
        cout << szBuf1 << '\n' << szBuf2 << endl;
    }
    return 0;
}
```


---

## 作者：b__b (赞：1)

~太好了是大模拟我们没救了~

此题难点在于输入与输出，~以及克服奇怪的题面和奇怪的翻译~。
## 题面简述
有若干个测试数据，每一个测试数据有两个行，分别代表两个多项式，将这两个多项式相乘。输入格式已比较透彻，只需注意 $x$ 与 $y$ 的输入顺序可能调换。

每一个测试数据输出两行，第一行为指数行，下一行为底数行。
> 第一行包含所有指数，相对于其余行适当定位信息。
## 实现
可以先将第一行的多项式输入完成，接着~由人教版八年级上册数学书~可得
> 一般的，**单项式与多项式相乘，就是用单项式去乘多项式的每一项，再把所得的积相加。**

> 一般的，**多项式与多项式相乘，先用一个多项式的每一项乘另一个多项式的每一项，再把所得的积相加**。

因此我们只需要在第二行不断输入单项式，遍历原多项式的每一项单项式相乘后放入结果。

需要进行指数的判重，可以用 map 实现，找到指数相同的单项式后将系数相加，因为 $ax^m+bx^m=(a+b)x^m$（其中 $a,b$ 均为常整数），合并后可能会出现系数为 $0$ 的情况，输出时要把这些系数为 $0$ 的单项式忽略。

> 输出行中的项必须按 $x$ 的幂次降序排列，对于给定的幂次按照 $y$ 的幂次递增的顺序。

例如，对于 $4y^{17}-1-x^5$，
1. 由于 $-x^5$ 是这个多项式内 $x$ 的次数最高的单项式，因此将 $-x^5$ 放到最前面。
2. 因为 $-1$ 可看作 $-y^0$，因此这是这个多项式内 $y$ 的次数最低的单项式，因此将 $-1$ 放到第二个。
3. 将 $4y^{17}$ 放到最后。

综上所述，这个多项式的排序结果为 $-x^5-1+4y^{17}$。

写成 C++ 代码可表示为：（```xcs``` 为 $x$ 的次数，```ycs``` 为 $y$ 的次数）
```cpp
if (a.xcs > b.xcs) return 1;
else if (a.xcs < b.xcs) return 0;
else return a.ycs < b.ycs;
```
> 第一行包含所有指数，相对于其余行适当定位信息。

个人感觉是本题最难的地方，理解和实现都有点困难（~~再加上奇怪的输出样例就更难了~~）。

下文中 $\mathrm{ans1}$ 为第一行的输出的缓冲，$\mathrm{ans2}$ 为第二行的输出的缓冲，$\mathrm{ansind}$ 为输出的字符数量，直接说输出时指输出到 $\mathrm{ans2}$。

用上文已排序的 $-x^5-1+4y^{17}$ 举例，
1. 先输出 $-x^5$，
> 如果第一项的系数为负，则在第一列中以一元减号开头，中间没有空白栏。

$\qquad$因此不需要在 $-$ 前后添加空格。

$\qquad$将 $-x$ 输出，完成后 $\mathrm{ansind}=2$。

$\qquad$开始输出指数 $5$，因为此时 $\mathrm{ansind}=2$，所以将 $5$ 放进 $\mathrm{ans1}$ 的第 $3$ 个字符，完成后 $\mathrm{ansind}=3$。

3. 开始输出 $-1$，
> 二进制正负（即输出中连接项的正负）前后都有一个空白列。

$\qquad$因此实际上要输出的为 $\;-\;1$（前后都有一个空格），输出后 $\mathrm{ansind}=7$。

4. 开始输出 $+4y^{17}$，同上文，实际上要输出的为 $\;+\;4y^{17}$，将 $\;+\;$ 输出后 $\mathrm{ansind}=10$，还剩下 $4y^{17}$ 需要输出。
   
   开始输出 $4y$，输出后 $\mathrm{ansind}=12$。
   
   接着输出指数 $17$，将 $17$ 放入 $\mathrm{ans1}$ 的第 $12$ 个字符，输出后 $\mathrm{ansind}=14$。

输出完成，$\mathrm{ans1}$ 的内容为：```  5         17```，
$\mathrm{ans2}$ 的内容为：```-x  - 1 + 4y  ```
（$\mathrm{ans2}$ 后面有两个空格的原因是因为题目要求上下两行输出长度相同，使用空格填充）。  
## 代码
```cpp
//喜欢我的抽象马蜂吗
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>
struct dan {
    int xs, xcs, ycs;
} oldduo[100], newduo[100];
char s[100], ans1[100], ans2[100];
int oldduoind, i, newduoind, ansind;
std::map<int, std::map<int, int>> pc;
int readd() { //这一个每次都会将i设为在当前的i后面的第一个非数字字符
    int ans = 0;
    for (; isdigit(s[i]); ++i) ans = ans * 10 + s[i] - '0';
    return ans;
}
void readdan(dan &dan) { //由于使用了上面的readd，因此会有readd的特性
    dan.xs = 1, dan.xcs = dan.ycs = 0;
    if (s[i] == '-') {
        if (isdigit(s[++i])) dan.xs = -readd();
        else dan.xs = -1;
    } else {
        if (s[i] == '+') ++i;
        if (isdigit(s[i])) dan.xs = readd();
    }
    while (isalpha(s[i])) if (s[i] == 'x') {
        if (isdigit(s[++i])) dan.xcs = readd();
        else dan.xcs = 1;
    } else if (s[i] == 'y') {
        if (isdigit(s[++i])) dan.ycs = readd();
        else dan.ycs = 1;
    }
}
void qc(int &ind, dan *duo) { //判重，如果有相同的项就合并
	auto it = pc.find(duo[ind].xcs);
    if (it == pc.end()) pc[duo[ind].xcs][duo[ind].ycs] = ind, ++ind;
    else {
    	auto nit = it->second.find(duo[ind].ycs);
    	if (nit == it->second.end()) it->second[duo[ind].ycs] = ind, ++ind;
    	else duo[nit->second].xs += duo[ind].xs;
	}
}
void scdannofu(dan &dan) { //输出一个单项式，这个单项式的项数已去除符号
    if (dan.xs != 1) ans2[ansind += sprintf(ans2 + ansind, "%d", dan.xs)] = ' ';
    else {
        if (!dan.xcs && !dan.ycs) {
            ans2[ansind++] = '1', ++ansind;
            return;
        }
    }
    if (dan.xcs) {
        ans2[ansind++] = 'x';
        if (dan.xcs > 1) ans1[ansind += sprintf(ans1 + ansind, "%d", dan.xcs)] = ' ';
    }
    if (dan.ycs) {
        ans2[ansind++] = 'y';
        if (dan.ycs > 1) ans1[ansind += sprintf(ans1 + ansind, "%d", dan.ycs)] = ' ';
    }
    ++ansind; //往后面放入一个空格
}
int main() {
    for (;;) {
        fgets(s, 100, stdin);
        if (s[0] == '#') break;
        for (i = oldduoind = newduoind = ansind = 0, pc.clear(); s[i] != '\n';) readdan(oldduo[oldduoind]), qc(oldduoind, oldduo);
        for (i = 0, pc.clear(), fgets(s, 100, stdin); s[i] != '\n';) {
            dan p;
            readdan(p);
            for (int j = 0; j < oldduoind; ++j) {
                dan &now = newduo[newduoind], &bef = oldduo[j];
                now.xs = p.xs * bef.xs, now.xcs = p.xcs + bef.xcs, now.ycs = p.ycs + bef.ycs, qc(newduoind, newduo);
            }
        }
        for (i = 0, std::sort(newduo, newduo + newduoind, [] (const dan &a, const dan &b) -> bool {
            if (a.xcs > b.xcs) return 1;
            else if (a.xcs < b.xcs) return 0;
            else return a.ycs < b.ycs;
        }); i < 100; ++i) ans1[i] = ans2[i] = ' '; //填充空格
        for (i = 0; !newduo[i].xs; ++i);
        if (newduo[i].xs < 0) ans2[0] = '-', ansind = 1, newduo[i].xs = -newduo[i].xs;
        for (scdannofu(newduo[i++]); i < newduoind; ++i) {
            if (newduo[i].xs < 0) ans2[ansind++] = '-', newduo[i].xs = -newduo[i].xs;
            else if (newduo[i].xs > 0) ans2[ansind++] = '+';
            else continue;
            ++ansind, scdannofu(newduo[i]);
        }
        ans1[ansind - 1] = ans2[ansind - 1] = 0, printf("%s\n%s\n", ans1, ans2);
    }
}
```

---

