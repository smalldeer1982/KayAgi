# [GCJ 2009 #1B] The Next Number

## 题目描述

你正在写一个数字列表。对于每个 $1 \leq i \leq 9$，你的列表包含所有十进制表示中恰好有 $D_i$ 个 $i$ 的数。你将这些数按升序排列。

例如，你可能正在写所有恰好包含两个 '1' 和一个 '5' 的数。你的列表将以 115、151、511、1015、1051 开头。

现在，给定 $N$，即你刚刚写下的最后一个数，请你计算列表中的下一个数是多少。

## 说明/提示

**限制条件**

**小数据集（9 分）**

- 时间限制：2 秒。
- $1 \leq T \leq 50$
- $1 \leq N \leq 10^6$

**大数据集（26 分）**

- 时间限制：3 秒。
- $1 \leq T \leq 500$
- $1 \leq N \leq 10^{20}$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
115
1051
6233```

### 输出

```
Case #1: 151
Case #2: 1105
Case #3: 6323```

# 题解

## 作者：b__b (赞：5)

用 STL 就是水题。

我们观察样例，我们容易发现一个性质：如果 $N$ 不是当前位数下的最后一个数字，那么 $N$ 的下一个数字就是 $N$ 的十进制表达的下一个排列。使用 STL 的 next_permutation 函数得到下一个排列。

那如果 $N$ 是当前位数下的最后一个数字呢？next_permutation 函数会在当前是最后一个排列时返回 false 并且将数组重新设置为第一个排列。我们观察样例可知如果增加一位后的第一个数会在原本的数的第一位的后面增加若干个 $0$（因为如果加其他数字或者加到其他地方都会使字典序变大导致放到后面），于是我们直接模拟即可。

更具体的，如果当前这个数字有 $k$ 个 $0$，那么我们需要添加 $k$ 个 $0$；因为我们需要加一位，因此最后需要增加 $k+1$ 个 $0$。
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
char s[25];
int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        while (!isalnum((fgets(s, 25, stdin), s[0])));
        int len = 0;
        while (isalnum(s[++len]));
        printf("Case #%d: ", i);
        if (std::next_permutation(s, s + len)) fputs(s, stdout);
        else {
            int n0 = 0; //统计0的数量
            for (; s[n0] == '0'; ++n0); //第一个排列里0一定在最前面
            putchar(s[n0]);
            for (int i = -1; i < n0; ++i) putchar('0'); //输出k+1个0
            fputs(s + n0 + 1, stdout); //输出剩下的部分
        }
    }
}
```

---

## 作者：ZYX0716 (赞：3)

# [P13435](https://www.luogu.com.cn/problem/P13435)适合大多数选手的方法。

## 思路：

本题是求**下一个排列**的升级版。将每组输入的数以字符串的形式读入，方便提取每一位上对应的数字。谈及新数的构成方式，这里我们分类讨论：

1. 首先考虑“刚刚写下的最后一个数”每一位上的数均**非递增**的情况。将其中**最小的非零数**作为最高位，次高位为**零**，其余数位用剩下的数字**从小到大**依次分配即可。

2. 一般情况下的处理方式与前者相比较为复杂。循环从后往前找到第一组（$i$，$i+1$）满足 $a[i]<a[i+1]$，先原封不动输出 $a[1]$ 至 $a[i-1]$，借助优先队列确定 $a[i]$ 到  $a[n]$ 中**大于** $a[i]$ 的**最小**的数 $x$ 并输出。其余的从小到大依次输出。

## AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	//快读可根据需求自行添加（本题时限为2、3秒）。
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		cin>>s;
		int pre=0,flag=-1,x;//pre记录上一位数，falg判断是否非递增。
		priority_queue<int,vector<int>,greater<int> >q,q1;//优先队列。
		for(int i=s.size()-1;i>=0;i--){
			if((s[i]-'0')>=pre){//大于或等于上一个数，入队。
				q.push(s[i]-'0');
				pre=s[i]-'0';//更新上一个。
			}else{
				flag=i;//第2中情况。
				while(!q.empty()){//找第一个大于s[i]-'0'的数。
					if(q.top()<=(s[i]-'0')){
						q1.push(q.top());//q1为辅助数组。
						q.pop();
					}else{
						x=q.top();
						q.pop();
						break;
					}
				}while(!q1.empty()){
					q.push(q1.top());
					q1.pop();
				}
				q.push(s[i]-'0');
				break;
			}
		}
		cout<<"Case #"<<tt<<": ";//标准格式。
		if(flag!=-1){//情况一。
			if(flag)cout<<s.substr(0,flag)<<x;
			else cout<<x;
			while(!q.empty()){
				cout<<q.top();
				q.pop();
			}
		}else{//情况二。
			int ans=1;
			while(!q.empty()){
				if(q.top()==0){
					ans++;
					q.pop();
				}else{
					cout<<q.top();
					q.pop();
					break;
				}
			}while(ans--){
				cout<<"0";
			}while(!q.empty()){
				cout<<q.top();
				q.pop();
			}
		}
		cout<<"\n";
	}
	return 0;//好习惯。
}
```

---

## 作者：BlackHoles (赞：2)

### 正解

我们将这一个数字列表根据位数区分类别。假如 $N$ 是当前类别的最后一个数，我们需要补充一个 $0$ 并输出下一个类别的第一个数。

反之，我们需要输出下一个数，使用 STL 的 next_permutation 函数可以轻松做到。

时间复杂度为 $O(Tn)$，其中 $n$ 为 $N$ 的位数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
string s;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> s;
		cout << "Case #" << t << ": ";
		if (next_permutation(s.begin(), s.end()))
			cout << s;
		else {
			int now = 0;
			while (now < s.size() && s[now] == '0')
				++now;
			cout << s[now];
			for (int i = -1; i < now; ++i)
				cout << '0';
			for (int i = now + 1; i < s.size(); ++i)
				cout << s[i];
		}
		cout << '\n';
	}
	return 0;
}
```

谢谢大家！

---

## 作者：New_Void (赞：2)

## [P13435 [GCJ 2009 #1B] The Next Number](https://www.luogu.com.cn/problem/P13435)

### 思路

这道题是求按照字典序最小排列，下一个是多少，显然我们可以使用全排列的 STL 模块，但是我们注意一个问题，就是当一个数字它的下一个数字不能用同样位数的数字表示，那么就要有加零的情况，所以我们可以输入字符串时，将字符串加一个前导零，这样全排列，如果全排列之后第一个仍然是零，就意味着，他的位数与输入的一样，那么我们就不用输出前导零，如果没有的话，那就直接输出全排列后的数字即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[105];
int read(){
    int k=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') k=k*10+c-'0',c=getchar();
    return k*f;
}
int main(){
    int T,idx=1;
    T=read();
    while (T--){
        cin>>(s+1);
        s[0]='0';
        int n=strlen(s+1);
        next_permutation(s,s+n+1);
        cout<<"Case #"<<idx<<": ";
        if (s[0]!='0') cout<<s[0];
        for (int i=1;i<=n;i++) cout<<s[i];
        cout<<endl;
        idx++;
    }
    return 0;
}

```

---

## 作者：yyycj (赞：1)

## 题目简述
给你一个数字 $K$，求第一个大于 $K$ 且其中与 $K$ 共同含有的数位的个数必须相同。

## 主要思路
不难发现，如果我们用字符串读入 $K$，那么答案就是 `next_permutation(K.begin(), K.end())`；但如果 $K$ 已经是最后一种排列，我们就应该将 $K$ 加一位数而且使得它最小，那么加的就一定是 $0$。加的过程就需要先将 $K$ 按升序排序，由于不能有前导零，所以需要将所有的前导零挪到最高且不是 $0$ 的数位后面，并再多加一个 $0$。

## AC Code
```cpp
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#endif
template<typename T> void read(T &x) { int f = 1; x = 0; char ch = getchar(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = getchar(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }x *= f; }
template<typename T, typename ...Args> void read(T &x, Args &...args) { read(x); read(args...); }
template<typename T> void print(T x) { if (x < 0) { putchar('-'); x = -x; }if (x > 9) { print(x / 10); }putchar(char(x % 10 + 48)); }
template<typename T, typename ...Args> void print(T x, Args ...args) { print(x); putchar(' '); print(args...); }

typedef long long ll;
typedef long double db;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
template<typename T1, typename T2> ll _pow(T1 a, T2 b) { ll x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }
// ----------------------------

// ----------------------------

// ----------------------------


int main() {
	int t; read(t);
	// ----------------------------
	int cnt;
	string k;
	for (int i = 1; i <= t; i++) {
		cin >> k;
		cout << "Case #" << i << ": ";
		if (next_permutation(k.begin(), k.end())) cout << k << '\n';
		else {  // 如果当前序列是最后一个排列，next_permutation 会返回 false
			sort(k.begin(), k.end());
			reverse(k.begin(), k.end());  // 为了判断前导零且高效，现将 k 翻转，利用 string 的 pop_back() 函数去掉前导零
			cnt = 0;
			while (k.back() == '0') {
				cnt++;
				k.pop_back();
			}
			cout << k.back(); k.pop_back();  // 先输出最高且不是 0 的数位
			for (int j = 1; j <= cnt + 1; j++) cout << 0;  // 为了增加一位多输出一个 0
			reverse(k.begin(), k.end());  // 不要忘了翻转再将剩下的全部输出
			cout << k << '\n';
		}
	}
	// ----------------------------
	
	return 0;
}
```

---

## 作者：__coderyc__ (赞：1)

## 思路
题意很好理解，简单来说就是需要找到比给定数字 $N$ 大的最小数字，且数字中各数字的出现次数与 $N$ 相同。

很明显，如果存在右边比它大的数字，采用贪心策略，从右向左找到**第一个可以交换**的位置，再按照题意，交换后对右边部分进行升序排序。

对于特殊情况，如果这个数已经是最大排列的时候，那就先交换第一个非零数字到首位，再插入一个零得到最小的大数。如果存在前导零肯定就直接~~消消乐~~消掉。

最后格式化输出就行了，这种输出方式属于是 GCJ 特色了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;string N;
string nextNumber(const string &s){
    string num=s;
    int n=num.size();
    int i=n-2;
    while(i>=0&&num[i]>=num[i+1])i--;
    if(i==-1){
        sort(num.begin(),num.end());
        int zero_pos=0;
        while(zero_pos<num.size()&&num[zero_pos]=='0')zero_pos++;
        if(zero_pos==num.size())return "0";
        swap(num[0],num[zero_pos]);
        num.insert(1,"0");
        return num;
    }
    int j=n-1;
    while(num[j]<=num[i])j--;
    swap(num[i],num[j]);
    sort(num.begin()+i+1,num.end());
    return num;
}
int main(){
    cin>>T;
    for(int k=1;k<=T;++k){
        cin>>N;
        string res=nextNumber(N);
        cout<<"Case #"<<k<< ": "<<res<<endl;
    }
    return 0;
}
```
时间复杂度为 $O(n \log n)$，可以通过此题（话说两三秒硬模拟都可以过吧）。

---

## 作者：the_Short_Path (赞：1)

## 思路
对于 $115$：
```
115
151
511
------
1015
1051
1105
1150
1501
1510
5011
5101
5110
------
10015
10051
……
```
可以看到，经过若干次排列，就会添加一个 $0$。那么可将其按位数分为若干区间。

将这个数存储为字符串，调用 `next_permutation()` 函数处理它的下一个排列。若函数返回了 `false`，则说明需要添加 $0$ 了。此时删去它前面所有的 $0$（因为它是升序排序过后的，$0$ 都在前面，设有 $x$ 个 $0$），并在第一位后添加 $x+1$ 个 $0$。
# 正解
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> s;
        if (!next_permutation(s.begin(), s.end())) {
            int cnt0 = 0;
            while (s[0] == '0') cnt0++, s.erase(0, 1); // 删除所有 0（设有 x 个）
            for (int i = 1; i <= cnt0 + 1; i++) s.insert(1, "0"); // 添加 x+1 个 0
        }
        cout << "Case #" << t << ": " << s << "\n";
    }
    return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
这其实就是一道全排列练习题。

题目中 $1 \le N \le 10^{20}$，这是一个很大的数字，并且要处理下一个排列，使用字符串存储显然是一个不错的选择。

在 STL 中，```next_permutation(a.begin(),a.end())``` 可以得到 $a$ 的下一个排列，但是当 $a$ 此时已经是最后一个排列的时候，$a$ 会变为第一个排列并且 ```next_permutation``` 会返回 false。我们以 `210` 为例，此时 `210` 是最后一个排列，排列后会变成 `012`，但是显然我们需要输出 `1002`，所以我们可以先统计出排列后前面零的个数并先输出所有零后面的那个数和所有零再加上一个零，然后就可以愉快地输出剩下的数了。

**要注意：** 用字符串类型时每个数的下标是什么。

[这里有对 next_permutation 的介绍。](https://blog.csdn.net/weixin_43991826/article/details/108816777)

## 参考代码
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=2e5+5;
int t;
string s,a,b;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>s;
		a=s;
		if(next_permutation(a.begin(),a.end())) cout<<"Case #"<<o<<": "<<a<<'\n';
		else{
			int p=0;
			for(int i=0;i<a.size();i++)
				if(a[i]=='0') p++;
				else break;
			cout<<"Case #"<<o<<": "<<a[p]<<a.substr(0,p)<<'0'<<a.substr(p+1,a.size()-p)<<'\n';
		}
//		cout<<a;
	}
}
/*
210
012
1002
*/
```

---

