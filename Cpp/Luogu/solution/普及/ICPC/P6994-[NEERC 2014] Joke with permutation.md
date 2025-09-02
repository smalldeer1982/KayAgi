# [NEERC 2014] Joke with permutation

## 题目描述

Joey 在一个文本文件中保存了一个从 $1$ 到 $n$ 的整数排列。所有的数字都以十进制数字的形式书写，没有前导空格。

然后 Joe 开了个玩笑：他把文件中的所有空格都去掉了。

帮助 Joey 恢复 Joe 玩笑后的原始排列！

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

感谢检查者提供者：@[Arcturus1350](\/user\/57699)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4111109876532
```

### 输出

```
4 1 11 10 9 8 7 6 5 3 2
```

# 题解

## 作者：Xu_Jinyi_2011 (赞：4)

[~~测试点下载：测试点.zip~~](https://vdse.bdstatic.com//192d9a98d782d9c74c96f09db9378d93.mp4?authorization=bce-auth-v1%2F40f207e648424f47b2e3dfbb1014b1a5%2F2021-07-12T02%3A14%3A24Z%2F-1%2Fhost%2F530146520a1c89fb727fbbdb8a0e0c98ec69955459aed4b1c8e00839187536c9)
## 算法选择：
首先我们可以知道，这道题中，数只有两种情况：  
1. 大于零的一位数。
2. 小于 $n$ 的两位数。

而且这道题的数据范围很小，所以可以使用深度优先搜索的解法。
### 确定 $n$：
因为是一串连续的正整数构成的序列，所以：
1. 当原始字符串的长度小于十时，$n$ 的值为原始字符串的长度。
2. 当原始的字符串的长度大于等于十时，$n$ 的值为原始字符串的长度减九的差除以二加九（两位数的长度为二，一位数的长度为一）。
### 搜索推出条件：
当用于存储答案的栈里的数的数量等于 $n$ 时，从第一个元素开始输出到最后一个。然后使用一个很好用的函数——`exit(0)`退出递归。
### 关于重复问题：
使用一个桶记录是否已经用过当前数不就解决问题了吗？
### 一点小问题：
必须判断两位数是否小于 $n$。题目里有解释，就别问我为什么了，半个小时血与泪的教训。
## 喜闻乐见的 $AC$ 代码分享
```cpp
#include <iostream>
#include <cstring>

using namespace std;

string s;
int a[60], b[60] = {1}, n;

void dfs(int it, int x) {
	if (x >= n ) {
	    for (int i = 0; i < n; i ++) {
	        cout << a[i] << ' ';
	    }
		exit(0);
	}
	if (it >= s.size()) return;
	if (!b[s[it] ^ 48]) {
		a[x] = s[it] ^ 48;
		b[s[it] ^ 48] = 1;
		dfs(it + 1, x + 1);
		b[s[it] ^ 48] = 0;
	}
	if (it < s.size() - 1 && !b[(s[it] ^ 48) * 10 + (s[it + 1] ^ 48)] && (s[it] ^ 48) * 10 + (s[it + 1] ^ 48) <= n) {
		int y = (s[it] ^ 48) * 10 + (s[it + 1] ^ 48);
		a[x] = y;
		b[y] = 1;
		dfs(it + 2, x + 1);
		b[y] = 0;
	}
}

int main() {
	cin >> s;
	n = s.size() <= 9 ? s.size(): 9 + (s.size() - 9)/2;
	dfs(0, 0);
	return 0; 
}
```
**~~各位大佬考虑点个赞？(orz)~~**

---

## 作者：chrispang (赞：2)

# 题目大意

给定一个 $1 \sim n$ 的排列，但由于中间没有空格分隔，所以让你把这个排列还原，只要任意一组解就可以。

# 思路

我们可以先把 $n$ 算出来，如果输入的 $\text{s}$ 的长度 $\le9$，我们可以知道里面都是一位数，所以 $n=|s|$；如果输入的 $\text{s}$ 的长度 $>9$，那么可以得知里面有两位数，所以 $n=\frac{|s|-9}{2}+9$。

知道了 $n$ 之后，题目就变简单了。我们通过暴力 `DFS` 就可以搞定了。

不过还需要注意两点：

- 由于是 $1 \sim n$，所以不能出现 $0$。
- 一个数只能出现一次，不能前面搜过后面又搜一遍。

上代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

string a;
int len, n, ans[60];
bool vis[110];
void dfs(int x, int sum) {
	if(x == a.size()) { //搜到头了 
		for (int i = 1; i <= n; i++) printf("%d ", ans[i]); //输出 
		exit(0);
	}
	if(sum > n) return;
	int w = a[x] - '0';
	if(!vis[w] && w >= 1 && w <= n) { //尝试将第一位看成一个一位数分隔出去
		vis[w] = 1; //标记
		ans[sum] = w; //记录
		dfs(x + 1, sum + 1);
		ans[sum] = 0;
		vis[w] = 0; //回溯 
	}
	if(x != a.size() - 1) {
		w = w * 10 + a[x + 1] - '0';
		if(!vis[w] && w >= 1 && w <= n) { //尝试把前两个位看成一个两位数一起分隔出去
			vis[w] = 1; //标记 
			ans[sum] = w; //记录 
			dfs(x + 2, sum + 1);
			ans[sum] = 0;
			vis[w] = 0; //回溯 
		}
	}
}

int main() {
	cin >> a;
	n = a.size() <= 9 ? a.size() : 9 + (a.size() - 9) / 2;
	dfs(0, 1);
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6994)

~~这题刚加了 spj 还一篇题解都没有，来写一篇~~

##  P6994 [NEERC2014]Joke with permutation

### 题意

有一个 $1\sim n$ 的排列，但是中间没有空格。要你根据这个串 $s$ 还原排列。$n\le50$。多解输出任意，保证有解。

### 题解

先根据 $s$ 的长度搞出 $n$。然后直接爆搜就行了。（[跑得飞快！](https://www.luogu.com.cn/record/108021485)）

当搜到某个位置时，依次向后面添加数位，如果前面没有用过而且数字在 $1\sim n$ 的范围时就继续搜索。

```cpp
int WS(int x){if(x<10)return 1;return 2;}//位数 因为 n<=50
string s;
int len,n,Ws;int a[55];
bool used[55];
void dfs(int dep,int pos)
{
	if(dep>n)//边界
	{
		if(pos==len+1)
		{
			for(int i=1;i<=n;i++)
				cout<<a[i]<<" ";
			exit(0);
		}
		return;
	}
	if(pos>len)return;
	int t;
	for(t=s[pos]-'0';pos<=len&&t<=n;pos++,t=t*10+s[pos]-'0')
		if(t&&!used[t])
		{
			a[dep]=t;used[t]=1;
			dfs(dep+1,pos+1);
			used[t]=0;
		}
}
void Solve()
{
	cin>>s;len=s.size();s=" "+s;
	for(;Ws<len;n++,Ws+=WS(n));//计算 n
	dfs(1,1);
}
```

就这么简单？就这么简单。

---

## 作者：A_small_WA (赞：1)

一道简单的深搜题。

思路十分简单，先算出 $n$ 是多少，再用一个 ```bj``` 数组检查。

由于 $n\le50$，所以数字最大为两位数，每次分别取出字符串前一位和两位，令这个数字为 $w$，则 $w$ 应符合以下两个要求：

- $1\le w\le n$（一定要判断 $1\le w$，因为有可能把 $0$ 算进去，我在这里卡了好久）
- $w$ 没被标记过（即之前的数列中没有 $w$）

最后用 $cnt$ 记录当前找出数的个数,用一个 ```ans``` 数组存答案，当 $cnt\le n$ 时输出即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
bool bj[114514],flag;
int ans[114514],k,n;
void dfs(int i,int cnt){
	if(cnt>k){
		for(int i=1;i<=k;i++){
			cout<<ans[i]<<" ";
		}
		exit(0);
	}
	if(i>=n) return;
	int w=s[i]-'0';
  //一位数
	if(!bj[w]&&w>=1&&w<=k){
		if(flag) return;
		ans[cnt]=w;
		bj[w]=1;
		dfs(i+1,cnt+1);
		bj[w]=0;
	}
	if(flag) return;
	if(i>=n-1) return;//防止到了字符串末尾还在搜
	w*=10,i++,w+=s[i]-'0';
  //两位数
	if(!bj[w]&&w>=1&&w<=k){
		ans[cnt]=w;
		bj[w]=1;
		dfs(i+1,cnt+1);
		bj[w]=0;
	}
	i--;
	return;
}
int main(){
	cin>>s;
	n=s.size();
	if(n<=9) k=n;
	else k=9+(n-9)/2;
	dfs(0,1);
	return 0;
}

---

## 作者：IAKIOI__ (赞：1)

# 前置知识

深度优先搜索、栈。

# 题目大意

给定一个字符串，要你将其划分为 $n$ 个不重复的数字，要求所有数都大于 $0$，小于等于 $n+1$，最后按在原字符串中的顺序输出。

# 思路

定义一个 ```vis``` 数组记录每个数是否被访问过，再定义一个栈记录答案，```num``` 记录不同的数的次数，通过深搜找出答案并输出。


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[100],num=0;
string s;
stack <int> q;
void dfs(int x){//x为在字符串中的下标
	if(num==n){
		stack<int>st;
		while(!q.empty()){
			st.push(q.top());
			q.pop();
		}
		while(!st.empty()){//栈应逆序输出
			cout<<st.top()<<" "; 
			st.pop();
		}
		exit(0);//强制结束程序
	}
	if(x>=s.size()){
		return ;
	}
	int i=(s[x]-'0');//一位数
	if(vis[i]==0&&1<=i&&i<=n){
		num++;
		vis[i]=1;
		q.push(i);
		dfs(x+1);
		vis[i]=0;//回溯
		q.pop();
		num--;
	}
	int j=i*10+(s[x+1]-'0');//二位数
	if(vis[j]==0&&1<=j&&j<=n){
		num++;
		vis[j]=1;
		q.push(j);
		dfs(x+2);
		vis[j]=0;//回溯
		q.pop();
		num--;
	}
}
int main(){
	cin>>s;
	n=(s.size()<10)?s.size():9+(s.size()-9)/2;//计算求出n
	s=' '+s;
	dfs(1);
	return 0;
}
```

---

## 作者：Daniel_xu (赞：1)

# P6994 Joke with permutation 题解——搜索基础
## 题意
把一段数字串分割成 $ n $ 份，使得这 $ n $ 个数字是 $ 1 \sim n $ 的一个排列，题目没有说明可能无解，则一定有至少一个解。
## 思路
可以使用深度优先搜索算法，搜索树为一个二叉树（一位数与两位数，两种可能），时间复杂度 $ O(2 ^ {n}) $，加上重复性剪枝，可以通过此题。
## 具体实现
- 用 $ vis $ 数组标记每一个数字是否被选过。
- 用 $ a $ 数组存储已经确定的数字。
- 用 $ cnt $ 变量表示目前已经确定了几个数字。
- 搜索分支：首先看单独一个数字，如果没有标记，则标记该数字，拓展搜索分支；接着看这个数字与下一个数字组成的数字，如果下标没有越界且没有被标记，则标记该数字，拓展搜索分支。
- $ 1 \sim n $ 的排列的最大数一定等于 $ n $,且每个数字不重复。$ vis $ 数组已经确保无重复数字，只需记录最大数字，在最后时判断是否与 $ cnt $ 相等即可。
## AC 代码
```cpp
#include<iostream>
#include<string>
using namespace std;
const int N=55;
bool vis[N];//标记数组 
int a[N];//存储已经确定的数字 
int len;//字符串长度 
string s;//输入的字符串 
int getNum(int l,int r){//将字符串转换为数字 
	int sum=0;
	for(int i=l;i<=r;i++){
		sum=sum*10+s[i]-'0';
	}
	return sum;
}
bool ok=false;//判断是否找到解 
void dfs(int pos,int cnt,int maxx){//深搜 从pos开始找，已经找到了cnt个，最大数为maxx 
	//递归边界 判断是否是1~n的排列 
	if(pos==len-1){
		if(maxx==cnt){ 
			ok=true;//已经找到
			//输出 
			for(int i=0;i<cnt;i++){
				cout<<a[i]<<" ";
			}
		}
		return;
	}
	//搜索分支（一位数，两位数） 
	for(int i=1;i<=2;i++){
		int next=pos+i;//下一个坐标 
		if(next<len){//在范围内（合法性剪枝） 
			int num=getNum(pos+1,next);//获取数字 
			if(num<=50 && !vis[num]){//n最大是50（合法性剪枝），判断是否重复（重复性剪枝） 
				vis[num]=true;//标记 
				a[cnt]=num;//更新 
				dfs(next,cnt+1,max(maxx,num));//继续搜索，更新最大数 
				if(ok){//如果已经找到解，直接return 
					return;
				}
				vis[num]=false;//回溯 
			}
		}
	}
}
int main(){
	//输入 
	cin>>s;
	len=s.length();
	//搜索 
	dfs(-1,0,0);
	return 0;
}

```

---

## 作者：zzwdsj (赞：1)

[P6994 [NEERC2014] Joke with permutation](https://www.luogu.com.cn/problem/P6994)

---
## 思路
这题的 $n$ 很小，不超过 $50$，不难想到使用搜索。由于分隔后每个数最多是两位数，可以每次尝试将第一位看成一个一位数分隔出去。再尝试把前两个位看成一个两位数一起分隔出去。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100]; //读入的字符串
int len,ans[51];
bool flag[51];
bool check()
{
	bool zero=false;//zero表示是否经过了0
	for(int i=1;i<=50;i++)
	{
		if(!flag[i])zero=true;//经过了0就标记
		if(zero&&flag[i])return false;//如果经过了0后面还有1，说明1不是连续的。
	}
	return true;
}
void dfs(int x,int sum)
{
	if(x==len+1)
	{
		if(check())
		{
			for(int i=1;i<sum;i++)printf("%d ",ans[i]);
			exit(0);
		}
		return;
	}
	if(!flag[a[x]-'0'])//尝试将第一位看成一个一位数分隔出去
	{
		flag[a[x]-'0']=1;
		ans[sum]=a[x]-'0';
		dfs(x+1,sum+1);
		flag[a[x]-'0']=0;
	}
	if(x!=len&&!flag[(a[x]-'0')*10+a[x+1]-'0'])//尝试把前两个位看成一个两位数一起分隔出去
	{
		flag[(a[x]-'0')*10+a[x+1]-'0']=1;
		ans[sum]=(a[x]-'0')*10+a[x+1]-'0';
		dfs(x+2,sum+1);
		flag[(a[x]-'0')*10+a[x+1]-'0']=0;
	}
}
int main()
{
	scanf("%s",a);
	len=strlen(a)-1;
	dfs(0,1);
	return 0;
}
```

---

## 作者：tiko_tao (赞：0)

### 题解：P6994 [NEERC2014] Joke with permutation


---
[题墓链接](https://www.luogu.com.cn/problem/P6994)  
这题乍一看是个爆搜。  
~~还真是。~~

**重点： $n\le 50$ 是数的种类个数！！！不是字符串长度！！！**

别问我为什么觉得这个是重点。。。  
~~数据开小居然是 WA 不是 RE 调死我了。~~

一开始我其实并没有往爆搜方向考虑，因为 ~~n 看错了~~考虑爆搜应该是枚举字符串的断点，那么时间复杂度应是  $O(2^n)$ 的，于是我直接放弃爆搜，去考虑线性。

......线性做不出来qwq。

后来经过我再次的思考，我发现在枚举断点的时候是有一定标准的，当我们根据字符串长度确定**这个排列的最大值**之后，相当于我们知道了两位数情况的十位最大值，于是可以加入一系列剪枝，这样复杂度会小很多很多，就不用担心超时的问题。  
再用类似**反悔**的做法，只要枚举到满足条件的一个排列就可以输出了qwq。

代码如下

```cpp
#include <bits/stdc++.h>
#define rep(i,a,n) for(int (i)=(a);(i)<=(n);(i)++)
#define pre(i,a,n) for(int (i)=(a);(i)>=(n);(i)--)
using namespace std;
const int N = 1000 + 10; //怒开1000！！！！！！awa 
int len[N], ans[N], t[N], mx, cnt = 0, n;	
bool vis[N], f = false;
void dfs(int x)
{
	if (f) return ;
	if (x == n + 1) 
	{
		f = true;
		return ;
	}
	if (t[x] > mx / 10 || x == n) 
	{
		if (vis[t[x]]) return ;	
		ans[++cnt] = t[x], vis[t[x]] = 1;
		dfs(x + 1);
		if (f) return ;
		cnt--, vis[t[x]] = 0;
	}
	else
	{
		if (t[x] == 0) return ;
		int d = t[x] * 10 + t[x + 1];
		if (d <= mx && vis[d] == 0)
		{
			ans[++cnt] = d; vis[d] = 1;
			dfs(x + 2);
			if (f) return ;
			vis[d] = 0, cnt--;
		}
		if (vis[t[x]]) return ;
		ans[++cnt] = t[x], vis[t[x]] = 1;
		dfs(x + 1);
		if (f) return ;
		vis[t[x]] = 0, cnt--;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	string s; cin >> s;
	n = s.size();
	rep(i, 0, n - 1) t[i + 1] = s[i] - '0';
	rep(i, 1, 50) len[i] = len[i - 1] + (i < 10 ? 1 : 2);
	rep(i, 1, 50)
		if(len[i] == n)
			mx = i;
	dfs(1);
	rep(i, 1, cnt) cout << ans[i] << " ";
	return 0;
}

```

---

## 作者：wht_1218 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6994)

---

题目是一道搜索，可以使用 `dfs` 进行求解。

由于 $n\le 50$，所以只有一位数或两位数。

注意判断两位数时**剩余字符串长度要大于 $1$**。

一位数或两位数的值**要在 $1$ 到 $n$ 之间**。 

注意搜索时**不要重复**，开一个 `vis` 数组。

**注意回溯！**

找到一个答案直接 `exit(0)` 就不用存了。

求 $n$：一位数长度为 $1$，两位数长度为 $2$，枚举 $n=1,2,3,4,\dots$，直至 $n$ 所对应的长度与字符串长度相等。

代码就不给了。

---

## 作者：suyi1111 (赞：0)

### 题意说明：
将 $1$ 到 $n$ 的随机一种排列去掉空格并给出，求原来的排列。

### 做法讲解：
暴力 `dfs` 就行了。

一个是层数，另一个是搜到现在要搜索的字符串。

先搜字符串第一位，再搜字符串前两位，再回溯。

### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n=0,kl,sl=0;
string k; 
bool vis[101];
int ls[101];
void dfs(int l,string s){//l是层数，s是当前的字符串 
	if(s==""||l==n+1){//找到了答案
		for(int i=1;i<=n;i++){
			if(vis[i]==0)return;
		}
		for(int i=1;i<=n;i++){
			cout<<ls[i]<<' ';
		}
		exit(0);
	}
	if(vis[s[0]-'0']==0&&s[0]-'0'<=n){//一位数 
		vis[s[0]-'0']=1;
		ls[++sl]=s[0]-'0';
		dfs(l+1,s.substr(1,s.size()-1));//递归
		sl--;
		vis[s[0]-'0']=0;
	} 
	if(s.size()!=1&&vis[(s[0]-'0')*10+s[1]-'0']==0&&(s[0]-'0')*10+s[1]-'0'<=n){//两位数 
		vis[(s[0]-'0')*10+s[1]-'0']=1;
		ls[++sl]=(s[0]-'0')*10+s[1]-'0';
		dfs(l+1,s.substr(2,s.size()-2));//递归
		sl--;
		vis[(s[0]-'0')*10+s[1]-'0']=0;
	} 
	return;
}
int main(){
	cin>>k;
	kl=k.size();
	for(int i=1;i<=50;i++){
		n+=(i<10?1:2);
		if(n==kl){
			n=i;
			break;
		}
	}
	dfs(1,k);
	return 0;
}

```

---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6994)

## 题意：

有一个 $1∼n$ 的排列，但是中间没有空格。要你根据这个字符串 $s$ 还原排列。$n \le 50$，多解输出任意，保证有解。

## 方法：DFS

## 思路：爆搜

用一个数组记录每个数是否被访问过，再定义一个栈记录答案，记录下不同的数的次数，找出答案后输出。

---

