# Queries for the Array

## 题目描述

Monocarp had an array $ a $ consisting of integers. Initially, this array was empty.

Monocarp performed three types of queries to this array:

- choose an integer and append it to the end of the array. Each time Monocarp performed a query of this type, he wrote out a character +;
- remove the last element from the array. Each time Monocarp performed a query of this type, he wrote out a character -. Monocarp never performed this query on an empty array;
- check if the array is sorted in non-descending order, i.,e. $ a_1 \le a_2 \le \dots \le a_k $ , where $ k $ is the number of elements in the array currently. Every array with less than $ 2 $ elements is considered sorted. If the array was sorted by the time Monocarp was performing that query, he wrote out a character 1. Otherwise, he wrote out a character 0.

You are given a sequence $ s $ of $ q $ characters 0, 1, + and/or -. These are the characters that were written out by Monocarp, given in the exact order he wrote them out.

You have to check if this sequence is consistent, i. e. it was possible for Monocarp to perform the queries so that the sequence of characters he wrote out is exactly $ s $ .

## 说明/提示

In the first test case, Monocarp could perform the following sequence of queries:

- add the integer $ 13 $ ;
- add the integer $ 37 $ ;
- check that the current array $ [13, 37] $ is sorted in non-descending order (and it is sorted).

In the fifth test case, Monocarp could perform the following sequence of queries:

- add the integer $ 3 $ ;
- add the integer $ 2 $ ;
- check that the current array $ [3, 2] $ is sorted (it is not);
- remove the last element;
- add the integer $ 3 $ ;
- check that the current array $ [3, 3] $ is sorted (it is);
- remove the last element;
- add the integer $ -5 $ ;
- check that the current array $ [3, -5] $ is sorted (it is not).

In all other test cases of the example test, it is impossible for Monocarp to write the sequence $ s $ when performing the queries according to the statement.

## 样例 #1

### 输入

```
7
++1
+++1--0
+0
0
++0-+1-+0
++0+-1+-0
+1-+0```

### 输出

```
YES
NO
NO
NO
YES
NO
NO```

# 题解

## 作者：Creeper_l (赞：21)

## 前言

这场 CF 是我赛后打的，vp 赛时没做出来，后来发现是有个地方理解错了，有一些细节没有考虑到。现在换了一种思路来写，感觉更清晰了。

## 做法

首先需要动态维护三个变量，$cnt$ 和 $finishsort$ 和 $unfinishsort$。这三个变量分别表示当前数字的个数，已经排好序的最后一个位置，和没有排好序的最前一个位置。首先我们知道如果序列要从有序的变为无序的，那么我们一定会贪心地将序列的最后一个位置变为无序的，因为这样才能更快地变回有序的，证明显然。接下来看四种操作：

- 在末尾新添加一个数

这时直接让 $cnt$ 加一就可以了，其它的变量的值都不需要改变。因为此时我们还不能判断出当前这个数应该排序还是不排序，需要参考之后的询问来判断。

- 删去末尾的一个数

首先要让 $cnt$ 减一。其次还要计算删去的这个数对整个序列的贡献，如果删去这个数之后 $finishsort > cnt$，那么要将 $finishsort$ 变为 $cnt$；如果 $unfinishsort > cnt$，即整个序列已经全部有序，那么直接将 $unfinishsort$ 变为 $0$。

- 判断这个序列无序

如果 $finishsort=cnt$ 或者 $cnt<2$，即整个序列有序，那么直接判断为不合法。否则如果 $unfinishsort$ 等于 $0$，就将 $unfinishsort$ 设置为当前位置。

- 判断这个序列有序

如果 $unfinishsort$ 不等于 $0$ 的话，那么一定是不合法的。否则将 $finishsort$ 设置为当前位置。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define re register
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 2e5 + 10;
int T,n,cnt,unfinish_sort,finish_sort;
char c[MAXN];
signed main()
{
	cin >> T;
	while(T--)
	{
		cin >> (c + 1);
		int len = strlen(c + 1),flag = true;
		cnt = finish_sort = unfinish_sort = 0;
		for(int i = 1;i <= len;i++)
		{
			if(c[i] == '0')
			{
				if(cnt == finish_sort || cnt < 2){flag = false;break;} 
				if(!unfinish_sort) unfinish_sort = cnt;
			}
			if(c[i] == '1')
			{
				if(unfinish_sort != 0){flag = false;break;}
				finish_sort = cnt;
			}
			if(c[i] == '+') cnt++;
			if(c[i] == '-') 
			{
				cnt--;
				if(cnt < unfinish_sort) unfinish_sort = 0;
				if(cnt < finish_sort) finish_sort = cnt;
			}
		}
		if(flag == true) puts("YES");
		else puts("NO");
	}
	return 0;
}

```


---

## 作者：jr_inf (赞：5)

因为插入和删除操作都在队尾，所以对序列前缀分析一下：
1. 若一个序列的答案为 `YES`，那么它前缀的答案也为 `YES`。（对于没检查过的序列）
1. 若一个序列的答案为 `NO`，那么它前缀的答案不确定。（对于没检查过的序列）
1. 若一个序列的某个前缀的答案为 `NO`，那么它的答案为 `No`。

根据第一点，维护最后一个答案为 `YES` 的前缀的下标；根据二、三点，维护第一个答案为 `NO` 的前缀的下标。对于四种情况分讨即可。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int iinf=2147483647;
const int N=2e5+10;
int t,len,min0,max1,nl;
bool flag;
char ch[N];
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		flag=0;
//    最后YES    首个No   序列长
		max1=-1,min0=iinf,nl=0;
		scanf("%s",ch);
		len=strlen(ch);
		for(int i=0;i<len;i++)
		{
			if(ch[i]=='+')nl++;
			if(ch[i]=='-')
			{
				if(max1==nl)max1--;
				if(min0==nl)min0=iinf;
				nl--;
			}
			if(ch[i]=='0')
			{
				if(nl<=1||max1==nl)
				{
					flag=1;
					break;
				}
				min0=min(min0,nl);
			}
			if(ch[i]=='1')
			{
				if(nl>1&&min0<=nl)
				{
					flag=1;
					break;
				}
				max1=nl;
			}
		}
		if(flag)puts("NO");
		else puts("YES");
	}
}
```


---

## 作者：Fire_Raku (赞：3)

不太一样的写法，感觉比较容易理解一点。码量也比较短。

首先我们要发现：一个序列如果目前是**升序**的，那么它不管**删多少个数**（中间不再加数），最终还是升序的；如果目前**不是升序**，那么不管**加多少个数**，最终也不是升序。

这启发我们用两个数组 $up_i$ 和 $down_i$ 记录当前长度为 $i$ 的序列是升序还是不是升序。如果存在一个时刻序列长度为 $i$，并且 $up_i$ 和 $down_i$ 都是 $1$，也就是既是升序也不是升序，那么就不合法。（情况1）

不合法的情况还有一种，就是当序列长度小于等于 $1$ 时，操作序列说此时不是升序，那么根据题意，也是不合法的。（情况2）

$up$ 和 $down$ 的转移非常简单，如果长度 $now$ 减 $1$，并且 $up_{now}=1$，那么 $up_{now-1}=up_{now}$，同时把 $up_{now}=down_{now}=0$，表示未知；如果长度 $now$ 加 $1$，那么只需要转移 $down_{now+1}=down_{now}$。

所以这题我们只需要发现上面的性质就好写了，虽然比别人多个数组来做有点蠢。

AC code:

```cpp
#include <bits/stdc++.h>
typedef long long ll;
int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		x = (x << 3) + (x << 1) + (c - '0');
		c = getchar();
	}
	return x * f;
}
int t;
char a[200010];
int up[200010], down[200010];
void Solve() {
	t = read();
	while(t--) {
		std::cin >> a + 1;
		int n = strlen(a + 1), now = 0;
		bool flg = 0;
		memset(up, 0, sizeof(up));
		memset(down, 0, sizeof(down)); //这样初始化没有 tle 有点神奇。
		for(int i = 1; i <= n; i++) {
			if(a[i] == '+' || a[i] == '-') {
				if(a[i] == '+') {
					down[now + 1] = down[now];
					now++;
				}
				else {
					down[now] = 0;
					if(up[now]) up[now - 1] = up[now]; //注意判断，因为这个调了好久qwq
					up[now] = 0;
					now--;
				}
			}
			else {
				if(now <= 1 && a[i] == '0') flg = 1; //情况2
				if(a[i] == '1') up[now] = 1;
				else down[now] = 1; //根据操作序列更新数组
				if(up[now] && down[now]) flg = 1; //情况1
			}
		}
		if(flg) std::cout << "NO\n";
		else std::cout << "YES\n";
	}
}

int main() {
	
	Solve();

	return 0;
}
```





---

## 作者：_299817_ (赞：1)

## Part 0: 题面翻译
> 注：这个翻译为机翻，仅供读者理解

Monocarp 有一个由整数组成的数组 $a$。最初，**这个数组是空的**。

Monocarp 对这个数组进行了三种查询：

- 选择一个整数，并将其 **到数组的末尾**。每当 Monocarp 执行一次这种类型的查询时，他都会写出一个字符 `+`；
- 从数组中删除 **数组的最后一个** 个元素。每次 Monocarp 执行这种类型的查询时，他都会写出一个字符（`-`）。Monocarp 从来没有在一个空数组上执行过这种查询；
- 检查数组是否以非降序排序，即 $a_1 \le a_2 \le \dots \le a_k$，其中 $k$ 是当前数组中元素的个数。**每个元素少于$2$的数组都被认为是排序过的**。如果在 Monocarp 执行该查询时数组已经排序，他就会写出字符 `1`。否则，他就写出一个字符 `0`。

给你一个由 $s$ 个 `0`、`1`、`+` 和 `-` 组成的字符序列。这些都是 Monocarp 写出的字符，并按照他写出的顺序给出。

你必须检查这个顺序是否一致，即 Monocarp 有可能进行查询，从而使他写出的字符顺序正好是 $s$。

## Part 1：主要思路
既然这道题要你问他具体给的操作是否合法，那么我们是不是就可以来模拟他的思路。来判断是否可以呢。

既然我们需要模拟，那么我们就必须明确一件事情：我们要尽量往“能实现”的方向进行模拟。

我们明确了这两点后，我们就来结合代码具体看怎么模拟的。

我们需要明确这几个量
```cpp
string s; // 输入的字符串
int ans[200010]; // 我们模拟出的数组
int cnt; // 我们模拟出的数组的长度
int stp = 0; // 上一个不能改变的状态的最小值
int now = 1; // 现在的状态，也就是我们现在的这个模拟出来的序列是递增的还是递减的，最开始默认为 1
int chng = 0; // 数组改变成非递增数列的位置
bool flag = 1; // 最后记录是否合法
```

这里可能有读者不太理解 `stp` 和 `chng` 是什么意思，我这里详细讲下：

“上一个不能改变的状态的最小值”，由于我们的算法的思想是一直保持现在的状态，当他查询状态与我们不同的时候，我们再“反悔”，折回去把以前的操作换掉。

那么，我们折回去的时间是有限度的，比如说给你这么几个操作：
`+ + 1 + - 0`，那么我们的模拟过程就是这样的。

```
0
0 0 // 这里需要判断是否不递减，我们发现符合预期，也就是 now = 1，所以我们就不用反悔
0 0 0
0 0 // 这里需要判断是否不递减，那么不符合，我们就需要反悔，也就是把最后一个数字改成 1（或者任何比 2 小的数字），那么这时候我们就会发现，当我们把最后一个 2 改掉时，第一次查询就不再会符合，那么我们就不能删掉，这个时候，最后一个数字就是“上一个不能改变的状态的最小值”
```

“数组改变成非递增数列的位置”，这里我们继续结合操作理解一下：

例如我们给的操作是 `+ + + 0 + + + 0 - - 1`。

我们继续模拟我们的操作过程：

```
0
0 0
0 0 0
0 0 -1 // 这个时候，我们发现 now = 0，那么也就说明我们要让最后一个数组变成非不减序列，那么我们就把最后一个数改掉就可以了
0 0 -1 -1
0 0 -1 -1 -1
0 0 -1 -1 -1 -1 // 这个时候，我们发现 now = 0，我们记录的状态与我们的查询状态相同，那么就不用管这个查询了
0 0 -1 -1 -1
0 0 -1 -1 // 最后这个地方如果我们要把整个序列的状态变成 1，那么我们就必须把最后几个 -1 删掉，那么我们的 chng 记录的也就是第一个 -1 出现的地方
```

理解了这两个量后，我们的问题就迎刃而解了：
```cpp
for(int i = 0; i < s.length(); i++){
    if(s[i] == '+'){ // 向这个序列的最后一位加上和上一个数相同的数
        cnt++; // 长度要 +1
        ans[cnt] = ans[cnt - 1]; // 加数
    }else if(s[i] == '-'){
        cnt--; // 减去这一个数，长度减一就可以了
        if(now == 0 && cnt == chng - 1){ // 如果我们减掉数后发现长度比我们“数组改变成非递增数列的位置”要前了，那么我们整个数列就变成非递减的了，这里读者可以理解一下
            now = 1; // 改变状态
            chng = 0;
        }
        stp = min(stp, cnt); // 如果我们减一后长度比“上一个不能改变的状态的最小值”小了，那么我们后面再加的话，显然就是可以改变的了
    }else if(s[i] == '0'){
        if(now == 0){ // 如果状态相等，也就不用做操作
            continue;
        }else if(cnt == 1){ // 如果数列的长度为 1，根据题意，0 一定是不合法的，我们就可以直接退出了
            flag = 0;
            break;
        }else if(stp == cnt){ // 这里也就说明我们不能改变最后一个数，也就说明不合法
            flag = 0;
            break;
        }
        ans[cnt] = ans[cnt - 1] - 1; // 否则我们把最后一个数减小一位
        chng = cnt; // 更新 chng
        now = 0; // 改变状态
    }else if(s[i] == '1'){
        if(now == 0){ // 如果现在的状态为 0，那么就不合法，这里不用另外判断是因为我们再加和减的过程中能把数列变成 1 的操作我们都做了，如果最后状态还是 0，也就说明不可能是 1，也就说明操作不合法
            flag = 0;
            break;
        }
        stp = cnt; // 更新 stp
    }
}
if(flag == 0){ // 输出
    cout << "No" << endl;
}else{
    cout << "Yes" << endl;
}
```

## Part 2：完整代码
具体注释上面已经讲过了，这里贴的是没有注释的（我赛时的源代码）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<stack>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n;
string s;
int ans[200010];
int cnt;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> s;
        n = s.length();
        cnt = 0;
        int stp = 0; // 上一个不能改变的状态的最小值
        int now = 1; // 现在的状态
        int chng = 0; // 改变成非递增数列的位置
        bool flag = 1;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '+'){
                cnt++;
                ans[cnt] = ans[cnt - 1];
            }else if(s[i] == '-'){
                cnt--;
                if(now == 0 && cnt == chng - 1){
                    now = 1;
                    chng = 0;
                }
                stp = min(stp, cnt);
            }else if(s[i] == '0'){
                if(now == 0){
                    continue;
                }else if(cnt == 1){
                    flag = 0;
                    break;
                }else if(stp == cnt){
                    flag = 0;
                    break;
                }
                ans[cnt] = ans[cnt - 1] - 1;
                chng = cnt;
                now = 0;
            }else if(s[i] == '1'){
                if(now == 0){
                    flag = 0;
                    break;
                }
                stp = cnt;
            }
        }
        if(flag == 0){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
    }
    return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

机翻害人，我还以为是 $1$ 和 $0$ 是对原序列排序，害得我比赛的时候都没对，恼。

首先，对于新加入的数字，我们可以先不确定是否有序，而是等到后续的 $1$ 或 $0$ 出现，再确定。

用 $num$ 表示目前有多少数字，用 $so$ 表示确定有序的数字中最后一位的位置，$nso$ 表示确定无序的第一位数字的位置。

那么，我们可以分几种情况讨论：

- 操作 $0$。

	- 如果满足 $so=num$，那么目前所有数字都一定排序，所以无解。
	- 如果满足 $num<2$，按照题意，一定有序，所以无解。
	- 其他情况都可以满足条件，此时对于 $[so+1,num]$ 的数字中有一个数字是无序的就行，这里选择最后一位，因为最后一位更容易被删除，后续满足条件的可能性更大，即 $nso=num$，注意：如果 $nso$ 本来就有值，代表有更靠前的无序数字，则无需更新 $nso$。
- 操作 $1$。
	- 如果此时 $nso>1$，代表前面有数字一定无序，所以无解。
	- 其他情况都可以满足条件，此时所有数都应该有序，即 $so=num$。
- 操作 $+$，为了使后续操作满足条件可能性更大，所以选择添加未知数字，即仅 $num+1$。
- 操作 $-$，先减 $num$，如果此时 $num<so$，则也要把 $so$ 减一，如果此时 $num<nso$，则代表无序的数字一定都被删了，所以更改 $nso$ 为 $0$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,num,so,flag,nso;
char ch[200005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",ch+1),n=strlen(ch+1),nso=num=so=flag=0;
		for(int i=1;i<=n;++i)
		{
			if(ch[i]=='+') ++num;
			if(ch[i]=='-') --num,nso=(num<nso)?0:nso,so=min(so,num);
			if(ch[i]=='1')
			{
				if(nso){flag=1;break;}
				so=num;
			}
			if(ch[i]=='0')
			{
				if(num<2||so==num){flag=1;break;}
				if(!nso) nso=num;
			}
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

---

## 作者：rainygame (赞：1)

分类讨论+模拟，感觉比 B 简单？

首先只在一侧加或减，考虑用栈来模拟。考虑每次都 `push` 不一样的数。可以注意到以任何一个数为栈顶的栈都是唯一的。**也就是说，用一个数可以表示唯一的一个栈。**

分类讨论 `NO` 的情况：

- 栈大小小于 $2$ 但是被判断为没有排序好。
- 本来以 $x$ 为栈顶的栈是排序好/没有排序好的，但现在反过来了。
- 栈内出现了没有排序好的部分，却被判断为排序好了。
- 排序好的栈的某个部分被判断为没有排序好。

首先第一种情况很好判断。

对于第二种情况，我们设一个数组 $v$，$v_x$ 表示以 $x$ 为栈顶的栈是否排序好了。是则 $v_x=1$；否则 $v_x=0$；无法判断则 $v_x=-1$。

然后每次遇到 `0` 和 `1` 判断一下就可以了。

对于第三种情况，我们设一个变量 $k$ 表示栈内 `0` 的数量，若 $k>0$ 时被判断为 `1`，就输出 `NO`。维护 $k$ 也比较简单。

对于第四种情况，我们显然无法将被判断为 `1` 的栈的所有数都更新 $v$。因此我们考虑更快的方法。

可以发现，如果涉及到查询一个栈的部分，就必须要删除至少一个数。所以在删除的时候，如果栈是排序好的，就把这个排序好的标记传递给下一个栈顶即可。

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x);
#define sp pc(' ');
#define el pc('\n');
#define pr(x) printf(x);
#define Yes pr("YES");
#define No pr("NO");
#define err assert(0);
//const int MAXN(1e5+1);
//const ll MOD(1e9+7);

ll re(){
    ll x(0), f(1);
    char ch;
    while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
    do{
        x = (x << 1) + (x << 3) + (ch ^ 48);
    }while ((ch = gc()) > 47);
    return x * f;
}

void uwr(ll x){
    ll tmp(x/10);
    if (tmp) uwr(tmp);
    pc(x-(tmp<<1)-(tmp<<3)^48);
}

void wr(ll x){
    if (x < 0){
        pc('-');
        x = -x;
    }
    uwr(x);
}

int ind, siz;
int val[200001];
stack<int> st;
string s;

void solve(){
	cin >> s;
	for (int i(1); i<=s.size(); ++i) val[i] = -1;
	while (!st.empty()) st.pop();
	ind = siz = 0;
	for (auto i: s){
		if (i == '+') st.push(++ind);
		else if (i == '-'){
			if (val[st.top()] == 0) --siz;
			if (val[st.top()] == 1){
				st.pop();
				if (!st.empty()) val[st.top()] = 1;
				continue;
			}
			st.pop();
		}else if (i == '0'){
			if (st.size() < 2){
				pr("NO")
				return;
			}
			if (val[st.top()] == -1){
				val[st.top()] = 0;
				++siz;
			}if (val[st.top()] == 1){
				pr("NO")
				return;
			}
		}else{
			if (st.size() < 2) continue;
			if (siz){
				pr("NO")
				return;
			}
			if (val[st.top()] == -1) val[st.top()] = 1;
			if (val[st.top()] == 0){
				pr("NO")
				return;
			}
		}
	}
	pr("YES")
}

int main(){
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);

    int t(1);
  t = re();
    while (t--){
        solve();
        el
    }

    return 0;
}
```


---

## 作者：AKPC (赞：1)

VP 赛 A 了。
### 思路
两个性质：

- 如果 $\{s1,s2,\dots,sn\}$ 不是升序, 则 $\{s1,s2,\dots,sn+k\}$ 也不是升序。
- 如果 $\{s1,s2,\dots,sn\}$ 是升序, 则 $\{s1,s2,\dots,sn-k\}$ 也是升序。

其中 $n,k\in N^*$，$n>k$。

其实没必要管放进去什么数字，只需要维护一下数字个数和每个位置是否升序（输入给定的条件，还有根据条件以及两个性质的推导）即可。

另外注意特判：

- 如果 $s$ 的大小 $\leq 1$，则 $s$ 一定是升序的。

### 代码
[link](https://www.luogu.com.cn/paste/bl6xzalc)

---

## 作者：cosf (赞：0)

## [CF1861C](https://codeforces.com/problemset/problem/1861/C) [Queries for the Array](https://www.luogu.com.cn/problem/CF1861C)

赛时罚了好几发……恶心题

## 思路

这里有一个显然的思路，就是记录（维护）三个数：序列长度 $l$，保证排序的前缀长度 $m$，从第 $d$ 位开始就一定无序。

处理好这三个的转移方式这道题就没什么难度了。

具体来说，对于各种操作可以这样维护：

- 初始化：$l = m = 0, d = +\infty$。
- 对于操作 `+`，我们只用将 $l$ 自增 $1$ 即可（该有序的还是有序，该无序的还是无序）。
- 对于操作 `-`，我们将 $l$ 自减 $1$，同时做 $m \gets \min\{l, m\}$（因为保证排序的长度不能超过那么长）。若 $l \lt d$，则 $d$ 变成 $+\infty$（保证无序的部分都删掉了）。
- 对于操作 `1`，若当前 $d \not= +\infty$，则显然 $d \le l$，也就是说，当前的一个后缀是无序的，即不成立。若成立，则做 $m \gets l$（必须全部都有序）。
- 对于操作 `0`，若当前 $m = l$，则显然不成立（全部有序）。若成立，则做 $d \gets l$（只需一位无序即可）。注意，当 $l \lt 2$ 时需要特判。

细节比较多，需要注意。

## 代码

```cpp
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string q;
        cin >> q;
        int l = 0, m = 0, d = 1145141; // 这个数能当作无穷大。
        int e = 0;
        for (char ch : q)
        {
            if (ch == '0')
            {
                if (l == m || l <= 1)
                {
                    e = 1;
                    break;
                }
                else
                {
                    d = min(d, l);
                }
            }
            if (ch == '1')
            {
                if (l >= d)
                {
                    e = 1;
                    break;
                }
                else
                {
                    m = l;
                }
            }
            if (ch == '+')
            {
                l++;
            }
            if (ch == '-')
            {
                l--;
                if (l < m)
                {
                    m = l;
                }
                if (l < d)
                {
                    d = 1145141;
                }
            }
        }
        if (!e)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
```


---

## 作者：Crazyouth (赞：0)

**翻译**

给你一个串和一个空序列，包含字符 `+`，`-`，`1`，`0`，其中 `+` 表示在序列中加入一个数，`-` 表示删去最新加入的数，`1` 表示当前序列是非严格递增的，`0` 表示当前序列不是非严格递增的，问你能否构造出一组合法的加入的数。

**分析**

我们不妨先考虑简单的情况。有如下一组数据：`++1-+0`，答案显然为 `NO`，赛时令我茅塞顿开。我们需要记录下两个东西，一个是可能的最靠后的未被排序的位置，另一个是可能的最靠前的被排序的位置，因为我们想尽量构造出合法的答案，所以必有一部分加入的数是既可以为 `1` 也可以为 `0` 的，这可以根据其他情况判断（位置指数在序列中的下标）。记前者为 $uns$，后者为 $sorted$，序列中数的个数为 $num$，对四个字符分别处理即可。

- `+`：很简单，`num++` 就没了。
- `-`：这里除了 `num--`，还需要更新 $uns,sorted$，因为这俩东西可能被删了。假如真的如此，$uns$ 恢复初始值无穷大，$sorted$ 减一，因为既然这个序列现在都是递增的，那么减一个肯定还是递增的。
- `0`：首先假如 $num<2$，直接 `NO`。其次假如 $num\le sorted$，也直接 `NO`。因为 $1$ 到 $sorted$ 这部分是递增的（尽管 $sorted$ 下标可能已不存在），现在说它不递增就自相矛盾，所以 `NO`。然后假如没有判 `NO` 的情况，就把 $uns$ 与当前的序列的数的数量取个 $\min$，因为现在已经不是递增的了。
- `1`：它与 `0` 的处理大相径庭，首先没有关于 $num$ 与常数的判断，其次它判 `NO` 的条件是 $num\ge uns$，因为 $uns$ 到 $num$ 这段不是递增的，现在说它递增也是自相矛盾。最后就是维护，把 $sorted$ 赋值为 $num$ 即可，表示这里已经是递增的了。

假如上述部分没有判 `NO` 返回的话，输出 `YES`，结束。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int flag=0;
		string str,s;
		cin>>str;
		s=' '+str;
		int uns=1e9,num=0,sorted=0;
		for(int i=1;i<s.size();i++)
		{
			if(s[i]=='+') num++;
			else if(s[i]=='-')
			{
				num--;
				if(uns==num+1) uns=1e9;
				if(sorted==num+1) sorted--;
			}
			else if(s[i]=='0')
			{
				if(num<=sorted)
				{
					cout<<"NO"<<endl;
					flag=1;
					break;
				}
				if(num<2)
				{
					cout<<"NO"<<endl;
					flag=1;
					break;
				}
				uns=min(uns,num);
			}
			else
			{
				if(num>=uns)
				{
					flag=1;
					cout<<"NO"<<endl;
					break;
				}
				sorted=num;
			}
		}
		if(!flag) cout<<"YES"<<endl;
	} 
}

---

