# Tavas and SaDDas

## 题目描述

Once again Tavas started eating coffee mix without water! Keione told him that it smells awful, but he didn't stop doing that. That's why Keione told his smart friend, SaDDas to punish him! SaDDas took Tavas' headphones and told him: "If you solve the following problem, I'll return it to you."

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535B/f91fa10ac839dabd2f33826f1fa403b926bbc6c1.png)The problem is:

You are given a lucky number $ n $ . Lucky numbers are the positive integers whose decimal representations contain only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

If we sort all lucky numbers in increasing order, what's the 1-based index of $ n $ ?

Tavas is not as smart as SaDDas, so he asked you to do him a favor and solve this problem so he can have his headphones back.

## 样例 #1

### 输入

```
4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
```

### 输出

```
2
```

## 样例 #3

### 输入

```
77
```

### 输出

```
6
```

# 题解

## 作者：XL4453 (赞：3)

### 解题思路：

每一个数一定比比这个数少至少一位的数要大，若设 $n$ 为这个数的位数，则比他位数少的数一共有：$2^{n}-2$。

然后考虑相同位数的数，这里将所有的 $4$ 替换成 $0$，$7$ 替换成 $1$，然后这个字符串在二进制下就是比这个数小的数的个数，直接加上即可。

注意最后要加上本身的 $1$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int num[1005],n,ans;
char c;
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}
int main(){
	c=getchar();
	while(c!='\n'&&c!='\r'){
		num[++n]=(c=='7');
		c=getchar();
	}
	for(int i=1;i<=n;i++)
	ans+=num[i]*pow(2,n-i);
	ans+=pow(2,n);
	ans--;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Buried_Dream (赞：3)

很明显吧，这题是分块打表的板子题。

分块打表很快啊，快如闪电，啪一下就切了。

这题连块长都不用卡，简直是分块打表的模板。

## 题意：
	
   幸运数字的定义：每一位只含有 $4$ 或 $7$。
   
   找到从 $1$ 到 $n$ 内幸运数字的个数。
   
## 思路：

分块打表，数据范围是 $1e9$，块长就设 $1e5$ 足够了。

写个判断函数开始打表就行了。

给出打表代码：

```cpp
bool Check(int x) {
	while(x) {
		if(x % 10 != 4 && x % 10 != 7) return false;
		x /= 10; 
	}return true;
}

int Bel = 1e5;

int cnt = 0;

signed main() {
	for(int i = 1; i <= 1e9; i++)  {
		if(Check(i)) cnt++;
		if(i % Bel == 0) printf("%lld,", cnt), cnt = 0;
	}
}
```

查询答案的时候，整块直接加，散块暴力求。

代码在剪切板里：https://www.luogu.com.cn/paste/x19xe57n


---

## 作者：Fcersoka (赞：2)

看到各位大佬都是用广度优先搜索写的 ，我只能默默地用起了我的深度优先搜索 。       
这里简单说一下题目意思 ，题目告诉我们存在一种幸运数字 ，而这种幸运数字是在十进制下只包含 $4$ 或 $7$ 的数 ，要我们求出 $1-n$ 之间有多少个这样的幸运数字 。  
由于这里的深搜是搜索数位 ，而这里 $n$ 的范围是 $n\leq10^9$，所以用深度优先搜索不会超时 。  
这里的 dfs 函数只需要一个参数 $sum$，$sum$ 表示当前枚举的数 ，这个枚举的数呢一定是幸运数字 ，所以要在每次递归的时候计数器加一 。在计数器加一前 ，要判断 $sum$ 是否大于 $n$，如果大于 $n$ 就要返回上一层递归 。dfs 里面需要分两种情况去搜索 ，一种是下一位是 $4$，一种是下一位是 $7$ ，dfs 的参数就是 $sum*10+7$ 或 $sum*10+4$。  
什么 ？就这么简单 ？当然不是 。这里出了些小问题 。
1. 这个数据很大 ，得开 long long；
2. 这个计数器的初始值得为 $-1$，因为 dfs 的第一次递归中 ，参数是 $0$，而计数器却加了一 ，导致答案出错了 。  
好了好了 ，说了这么久 ，该放代码了 ，代码如下 。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans=-1;
void dfs(ll sum){
	if(sum>n)//边界
	return;
	ans++;
	dfs(sum*10+4);//两种情况
	dfs(sum*10+7);
}
int main(){
	cin>>n;
	dfs(0);
	cout<<ans;
	return 0;
}
```
感谢您的观看 ，谢谢 ！

---

## 作者：phil071128 (赞：1)

## 题解 CF535B 【Tavas and SaDDas】

题意：找出1~n之间的所有**只包含4或7**的数字个数

例如：1~47之间有4，7，44，77这4个数


------------


一道很不错的**搜索**练习题，用搜索思路较为简单。

因为我是蒟蒻，所以就发个只有蒟蒻我才会的**深度优先搜索DFS**的做法吧

 ## DFS框架
 ```cpp
void dfs(){
    if(到达状态)
    {
        ... //根据题意添加 
        return; 
    }
    if(越界或不合法状态) return; 
    if(特殊状态) // 剪枝
         return;
    for(扩展方式)
    {
        if(扩张方式所到达状态合法)
        {
            修改操作； // 根据题意添加
            标记；
            dfs();
            (还原标记);
            //是否加上还原标记根据题意
            //如果加上还原标记就是回溯法 
        }
    }
}
```



## 这里有个小小的结论：

- 如果这个数是Lucky Number，那么这个数的末尾加上4或者加上7一定是Lucky Number

- 例如 4是一个Lucky Number ，那么44，47也都是，继续往下，444，447，474，477也都是Lucky Number

- 那么在末尾加上4或者7并不需要字符串一类的操作，只需要将它*10再加上4或者7即可。

- 所以，我们分别进行dfs(4)和dfs(7),可以得到两个互不相同且不重不漏的Lucky Number数列。这样这道题就很简单了吧






### 注意事项
1. 需要开**long long**，第30个点过不去的同学可以看一下是不是没有开**long long**的问题

1. 需要先dfs(s * 10 + 4),再dfs(s * 10 + 7) 



## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans;  //Lucky Number的个数
long long n;   //
void dfs(long long s){	//注意开long long
      	//s一定是Lucky Number
	if(s<=n){ //如果这个数小于或等于n，合法，可以进行搜索
		ans++; //计数器++
		dfs(s*10+4);  //将这个Lucky Number 末尾加上4，依旧是Lucky Number
		dfs(s*10+7);  //同理
	}	
    return ; //如果当前的这个数大于n，那么结束搜索搜索结束
}
int main(){
	cin>>n;
	dfs(4);  //搜索开始（这个数列每个数的首位都是4）
	dfs(7);	//这个数列每个数的首位都是7
	cout<<ans;  //输出幸运数字总数
	return 0;
}
```
求各位管理大大能过~~~

---

## 作者：lucky2008 (赞：0)

# CF535B题解

## [题目传送门](https://www.luogu.com.cn/problem/CF535B)

### 题目大意

求 $1 \sim~ n$ 中只含 $4$ 或 $7$ 的数的个数。

### 思路

这题数据量较大从 $1 \sim~ n$ 逐个枚举肯定会超时，所以我们换个思路，直接枚举每一个只含 $4$ 或 $7$ 的数。

可以直接用广搜实现，每次将符合要求的数入队，以此搜索新的数，一直搜索到搜索不了位置。

## AC 代码

最后附上ac代码

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
long long bfs(int n)//广搜函数 
{
	queue<long long> q;//数据有点大，用long long比较 保险 
	long long ans=0;
	q.push(0);//队列一开始是0，方便后面生成只含4或7的数 
	while(!q.empty())//判断队列是否为空 
	{
		long long x=q.front()*10+4,y=q.front()*10+7;//生成下两个只含4或7的数 
		if(x<=n) 
		{
      		//如果符合要求就入队，并将ans加一 
			q.push(x);
			ans++;
		}
		if(y<=n)
		{
			//同理，如果符合要求就入队，并将ans加一  
			q.push(y);
			ans++; 
		}
		q.pop();//已经生成完新的数了，队头就没用了，就要出队 
	}
	return ans;//返回答案 
}
int main()
{
	long long n;
	scanf("%lld",&n);//输入 
	printf("%lld",bfs(n));//输出
	return 0;//完结撒花 
}
```



---

## 作者：_Qer (赞：0)

这里提供一种广搜做法

从高位开始生成Lucky Number，优先生成下一位为4的，用cnt记录生成了几个，当生成的数是要求的数时，cnt即为它的排名

```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace io;
int x, cnt = -1;
//一开始入队的是0，不算LuckyNumber，循环中先++cnt再判断，故cnt从-1开始
queue<int> que;
int main() {
    cin >> x;
    que.push(0);
    int u = 0;
    while (true) {
        u = que.front(), ++cnt;
        que.pop();
        if (u == x) {
            cout << cnt << endl;
            return 0;
        }
        que.push(u * 10 + 4);//要先生成高位较小的数
        que.push(u * 10 + 7);
    }
    return 0;
}
```


---

## 作者：Acerkaio (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF535B)
- ## 算法
深度优先搜索。
- ## 思路
一个数在十进制下只包含 4 和 7。琢磨这句话，联系算法很容易想到这个数一位只有两种情况，即 4 和 7，所以搜素每一位每种情况，边界即是 $n$。
- ## CODE
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n = 0, ans = 0, num = 0;
inline void dfs(int p) {
	if(p>n)
		return ;
	ans = num;
	num++;
	dfs(p * 10 + 4);
	dfs(p * 10 + 7);
}
signed main() {
	cin >> n;
	dfs(0);
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这道题目其实还是挺简单的。

确定那个数是a位数，是a位数中的第几个就行了。
```
#include<bits/stdc++.h>
using namespace std;
register int main()
{
    int n=0;
    string s;
    cin>>s;//字符串读入
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='7') n+=pow(2,s.length()-i-1);//排在第n个
    }
    cout<<n+pow(2,s.length())-1<<endl;//s.length()位数
    return 0;
}
```

---

