# [CCC 2025 Junior] Sunny Days

## 题目背景

本题满分 15 分。

## 题目描述

CEMCity 拥有大量历史天气数据。数据中每一天都被标记为晴天（S）或降水日（P）。Jeremy 想要找出最长的连续晴天记录。然而，这些数据中恰好有一天的记录是错误的（但 Jeremy 不知道是哪一天）。

你的任务是帮助 Jeremy 计算出可能的最长连续晴天天数。

![](https://cdn.luogu.com.cn/upload/image_hosting/mirndz24.png)

## 说明/提示

**样例输入输出解释**

如果第三天的数据是错误的（实际应为晴天），那么从第二天到第五天将出现连续 4 天的晴天记录。这是可能的最长连续晴天天数。也就是说，无论哪一天的数据是错误的，都不会出现 5 天或更长的连续晴天。

以下表格展示了 15 分的分配情况：

|分值|描述|数据范围|
|:-:|:-:|:-:|
|2|历史数据天数较少。数据由连续的 S 和连续的 P 组成（其中一个部分可能为空）|$N\leq 1000$|
|4|历史数据天数较少。数据中 S 和 P 可能交替出现|$N\leq 1000$|
|9|历史数据可能包含大量天数|$N\leq 500\,000$|

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
P
S
P
S
S
P
P
S```

### 输出

```
4```

# 题解

## 作者：Zskioaert1106 (赞：1)

题目传送门：[P12612 [CCC 2025 Junior] Sunny Days](https://www.luogu.com.cn/problem/P12612)

坑坑坑。

### 做题过程

不难想到简单的贪心：如果两段 $\texttt S$ 之间只隔有一个 $\texttt P$，则可以将这两段合并。于是我们可以用如下方法统计：

- 记 $p$ 代表上一个字符是否是 $\texttt S$，$s1$ 和 $s2$ 分别代表上述两段 $\texttt S$ 的前一段和后一段。

- 若当前元素为 $\texttt S$：  
如果 $p$ 为真，则 $s2 \leftarrow s2+1$；  
否则 $s2$ 初始化为 $1$，$p$ 改为真。

- 若当前元素为 $\texttt P$：  
如果 $p$ 为真，$s1 \leftarrow s2$，将 $p$ 设为假；
否则将 $s1$ 和 $s2$ 同时清零。（两段中间隔了不止一个 $\texttt P$）

每次遇到  $\texttt S$ 都更新答案：$ans = \max(ans,s1+s2+1)$。

好的，这样你可以[拿到 $13$ 分](https://www.luogu.com.cn/record/218603019)了。

我们漏掉了什么？

首先，因为必须修改一位，所以如果全是晴天的话，结果是 $n-1$。

其次，按照上面的算法，如果全是阴雨结果为 $0$，但实际上是 $1$。

没了。

### 代码实现

```cpp
#include<iostream>
using namespace std;
int s1,s2,ans;
bool p,p1;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        char a;
        cin>>a;
        if(a=='S'){
            if(p)s2++;
            else s2=1,p=1;
            ans=max(ans,s1+s2+1);
        }
        else{
            p1=1;
            if(p){
                p=0;
                s1=s2;
            }
            else s1=s2=0;
        }
    }
    if(!ans)ans=1;
    if(!p1)ans=n-1;
    cout<<ans;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/218607240)。

---

## 作者：Kratos_Charger (赞：1)

## P12612 [CCC 2025 Junior] Sunny Days 题解

### Main

给定一个由晴天和降水日，也就是 `S` 和 `P` 组成的历史天气数据序列，其中恰好有一天的记录是错误的（但不知道具体是哪一天）。需要找出在修正一个错误记录的情况下，可能的最长连续晴天天数。

### Solution

用一个数组 $a_i$ 表示以第 $i$ 天结尾的连续 `S`，通过正向遍历填充。数组 $b_i$ 表示以第 $i$ 天开头的连续 `S`，通过逆向遍历填充，也就是预处理。

对于每个位置 $i$，如果是 `P`，考虑将其改为 `S` 后能连接左右两段 `S` 长度为 $a_{i-1}+b_{i+1}$。如果是 `S`，则直接比较当前连续段长度。注意记得处理全 `S` 或全 `P` 的特殊情况。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
char c[500005];
int a[500005],b[500005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>c[i];
    // 计算前缀数组a[i]：以i结尾的连续S天数
    for(int i=1;i<=n;i++){
        if(c[i]=='S') a[i]=a[i-1]+1;
        else a[i]=0;
    }
    // 计算后缀数组b[i]：以i开始的连续S天数
    for(int i=n;i>=1;i--){
        if(c[i]=='S') b[i]=b[i+1]+1;
        else b[i]=0;
    } 
    int ans=0;
    int cnt=0;
    // 统计总晴天数
    for(int i=1;i<=n;i++)
        if(c[i]=='S') cnt++;
    // 处理全S或全P的特殊情况
    if(cnt==n){
        cout<<n-1;
        return 0;
    }
    if(cnt==0){
        cout<<1;
        return 0;
    }
    // 遍历每一天，计算可能的最大值
    for(int i=1;i<=n;i++){
        if(c[i]=='P'){
            // 如果修改这个P为S，可以连接左右两边的S序列
            int temp=a[i-1]+1+b[i+1];
            ans=max(ans,temp);
        }
        else{
            // 不修改的情况，直接取当前连续S序列的长度
            ans=max(ans,a[i]);
            ans=max(ans,b[i]);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：guoshengyu1231 (赞：1)

# 题解：P12612 [CCC 2025 Junior] Sunny Days
## 题意分析
我们有一系列的历史天气数据，每天被标记为晴天或降水日。这些数据中恰好有一天的记录是错误的（但不知道是哪一天）。我们的任务是找出在最多可以修正一个错误记录的情况下，可能的最长连续晴天天数。
## 方法一：双指针法
首先我们需要定义两个指针 $l$ 和 $r$，还需要定义一个布尔变量 $flag$，表示是否出现了一次雨天，接下来考虑右指针 $r$ 该如何移动。  
- **当后一天是晴天**：此时我们直接移动指针 $r$ 即可。
- **当后一天是雨天**：此时如果 $flag$ 的值为真，表示**没有**出现一次雨天，此时还是直接移动指针 $r$，但如果此时 $flag$ 的值为假，那就不能再移动了，此时更新答案 $ans$。

当移动完右指针 $r$ 后，我们直接移动左指针 $l$ 直到再次满足条件即可。

**注意事项**：由于题目说是**恰好**有一天的数据是错误的，所以当所有天都是晴天时，那必然有一天是雨天，所以特判这种情况，让最终答案减 $1$。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l=1,r=0,ans;
char a[500005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	bool flag=true;
	while(r<n)
	 {
	 	while(r<n&&(flag||a[r+1]=='S'))
	 	 {
	 	 	r++;
	 	 	if(a[r]=='P') flag=false;
	 	 }//移动右指针r
	 	if(flag&&r-l+1==n) 
	 	 {
	 	 	ans=max(ans,r-l);
	 	 	continue;
	 	 }//特判
	 	ans=max(ans,r-l+1);
        r++;
	 	while(l<r&&a[l]!='P') l++;//移动左指针l
        l++;
	 }
	cout<<ans;
	return 0; 
} 
```
## 方法二：动态规划
其实这题还可以用动态规划的做法去做。设 $dp_{i,0}$ 代表此时数据没有错误的情况下，以第 $i$ 天为结尾的最长连续晴天的长度，而 $dp_{i,0}$ 代表此时数据有一处错误的情况下，以第 $i$ 天为结尾的最长连续晴天的长度。不难想出状态转移方程。
- 当第 $i$ 天是晴天，此时 $dp_{i,0}=dp_{i-1,0}+1$，$dp_{i,1}=dp_{i-1,1}+1$。
- 当第 $i$ 天为雨天，此时 $dp_{i,0}=0$，$dp_{i,1}=dp_{i-1,0}+1$。

最终答案为 $\max_{i=1}^{i\le n}\max(dp_{i,0},dp_{i,1})$。 $\\$ 
由于 $dp_i$ 都只与 $dp_{i-1}$ 有关，所以我们可以滚动数组优化。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,ans;
int d1,d2;//dp[i][0],dp[i][1]
bool flag=true;
char a[maxn];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	 {
	 	cin>>a[i];
	 	if(a[i]=='P') flag=false;
	 }
	for(int i=1;i<=n;i++)
	 {
	 	if(a[i]=='S'){d1++;d2++;}
	 	else{d2=d1+1;d1=0;}//状态转移
	  	ans=max(ans,max(d1,d2));
	 }
	if(flag) ans--;
	cout<<ans;
	return 0;
}
```

---

## 作者：Gilbert1206 (赞：1)

## 题解：P12612 [CCC 2025 Junior] Sunny Days

[题目传送门](https://www.luogu.com.cn/problem/P12612)

## 题意

这里有 $N$ 天历史数据的天数，每一行有一个字符。如果字符是 `S`，则代表是晴天。如果字符是 `P`，则代表是雨天。此时正好有一天的天气记错了，让你求最大晴天数。

## 思路

这道题明显暴力会超时，所以这道题肯定是贪心的思路来做。首先我们需要把当前的最长连续的晴天数记录下来。


```cpp
for(int i=0;i<n;i++){
    cin>>a[i];
    if(a[i]=='S'){
        now++;
    }
    else{
        b[i-1]=now;//此时记录他的最长当前连续晴天数。
        now=0;
    }
}
b[n-1]=now;
```

但此时他只有每段的最后一个标记了他的天数，我们需要把每段的每一个都标上它那一个段的晴天数。那一段的长度就为 $b_i$。


```cpp
int t=0,nk=0;
for(int i=n-1;i>=0;i--){
	if(b[i]!=0){//如果那一个地方被标记过的，说明这一段的最后一个标记了，我们也要把前b[i]-1个也标记为b[i]。
		t=b[i];
		nk=b[i]-1;
	}
	else{
		if(t!=0&&nk>0){//判断如果b[i]=0,并且这个格子需要填数字。
			nk--;//此时又添了一个，标记的数量也随之减少1。
			b[i]=t;	
		}
	}	
}
```
最后如果 $b_i=0$，我们就需要把那天天气变成晴天，看连上后连续晴天数为多少，因为我们此时知道它左边的晴天数和右边的晴天数，所以得到连起来的晴天数公式应为 $b_{i-1}+b_{i+1}+1$，最后求得最大值。

当然如果一个 $b_i=0$ 都没有，说明了本来所有天都是晴天，但又要一天是相反的天气，则答案就为 $N-1$ 或者是任意一个 $b_i-1$。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char a[650000];
int b[650000];
signed main(){
	int n,now=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]=='S'){
			now++;
		}
		else{
			b[i-1]=now;
			now=0;
		}
	}
	b[n-1]=now;
	int t=0,nk=0;
	for(int i=n-1;i>=0;i--){
		if(b[i]!=0){
			t=b[i];
			nk=b[i]-1;
		}
		else{
			if(t!=0&&nk>0){
				nk--;
				b[i]=t;	
			}
		}
	}
	int anss=0;
	for(int i=0;i<n;i++){
		if(b[i]==0){
			anss=max(anss,b[i-1]+b[i+1]+1);
		}
	}
	if(anss==0){
		anss=b[0]-1;
	}
	cout<<anss;
    return 0;
}

```

---

## 作者：WoW_BBQ (赞：1)

## 解题分析

先特判，若全是晴天输出 $n-1$，因为必定要晴改雨一天。

若全是雨天输出 $1$。

然后将晴雨的交替情况分别计入两个数组中。

如果发现两段晴天中只有一天雨天，就可以将他们连起来。

否则就只能在晴天基础上加上一天。

统计出最大答案即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,cnt=1,to[500005],f[500005];
char a[500005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    int pre=1;while(a[pre]=='P')pre++;
    if(pre==n and n!=1){cout<<1;return 0;}
    f[1]+=(pre-1);
    for(int i=pre;i<=n;i++){
        if(a[i]=='P'){if(a[i-1]=='S')cnt++;f[cnt]++;}
        if(a[i]=='S'){to[cnt]++;}
    }
    int ans=0;
    if(cnt==1 and pre==1){cout<<n-1;return 0;}
    for(int i=1;i<=cnt;i++){
        ans=max(ans,to[i]+1);
        if(f[i]==1)ans=max(ans,to[i]+to[i-1]+1);
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：chenyimo1204 (赞：1)

### 题目大意

有 $n$ 天天气，要么是 `S`（阳光明媚的天），要么是 `P`（降水的天），但是有一天天气是错的，找出最长可能的连续阳光明媚的天数。

### 题目思路

我们的任务是修改一天的天气后让连续阳光明媚的天数变得最长，所以要把一天降水的天当做阳光明媚的天。

定义一个 $ans$ 表示最后答案，$ans$ 初始值为 $0$，如果全为阳光明媚的天，输出 $n - 1$，应为有一天是错的。

$day$ 统计降水的天数，若连续出现大于两天降水的天，就循环判断一下就行了，刷新 $ans$，最后输出 $ans$ 就行了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum=0;
char a[500005];
int main( ) {
	cin>>n;
	for(int i=0; i<n; i++) {
		cin>>a[i];
		if(a[i]=='S') {
			sum++;
		}
	}
	if(sum==n) {
		cout<<n-1;
		return 0;
	}
	int l=0,ans=0,day=0;
	for(int i=0; i<n; i++) {
		if(a[i]=='P') {
			day++;
		}
		while(day>1) {
			if(a[l]=='P') {
				day--;
			}
			l++;
		}
		ans=max(ans,i-l+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：syx_2014 (赞：1)

~~话说标签里的递推和双指针用的上吗。~~

贪心（也许）。

让历史天气里最长连续晴天天数最大，自然要把紧挨着 `S` 的 `P` 变成 `S`，因为这样能让一个连续段的长度更长。

分为两种情况：

- 如果变成 `S` 的 `P` 后边没有 `P`，那两段 `S` 序列就会连在一起，别忘了再加上 $1$。（有前后两种情况，要分成两个 `if`）。
- 如果变成 `S` 的 `P` 后边（或前面）有 `P`，那那一段 `S` 的序列就只能加 $1$。（这个虽然也有前后两种情况，但写一个 `if` 就行了）。

于是我们把每一段连续的 `S` 和 `P` 序列都预处理出来，然后进行以下步骤：

1. 看看这个长度所对应的是连续的 `S` 序列还是 `P` 序列。（我用了一个 `bool` 变量 `c` 来记录，$0$ 为 `P`，$1$ 为 `S`）。
2. 如果是 `S` 序列，判断一下上面的两种情况，然后发更新最大值。
3. 如果是 `P` 序列，跳过。
4. 将 `c` 取反，因为每一段连续序列结束后肯定会是下一段**字母不同**的连续序列。


------
另外，这题有很多坑！！！

1. 一定要判断 `c` 一开始是 $1$ 还是 $0$。
2. 最后 `c` 不要忘了取反。
3. `Subtask #1` 里有全 `S` 和全 `P` 的情况，注意特判！

### AC code

```cpp
//这里为了让大家看得清楚，我特意用换行分隔了不同的步骤。
#include<bits/stdc++.h>
using namespace std;

int n;
char s[500100];
int a[500100];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	//特判全 S 全 P 的情况。
	bool S=1,P=1;
	for(int i=1;i<=n;i++){
		if(s[i]!='S') S=0;
		if(s[i]!='P') P=0;
	}
	if(S==1){
		cout<<n-1<<'\n';
		return 0;
	}
	if(P==1){
		cout<<1<<'\n';
		return 0;
	}
	//预处理每个连续段的长度。
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(s[i]!=s[i-1]) a[++cnt]=1;
		else a[cnt]++;
	}
	//把将 P 变成 S 的两种情况判断一下。
	int maxx=-1;
	char c=(s[1]=='S');
	for(int i=1;i<=cnt;i++){
		if(c==1){
			if(a[i+1]==1) maxx=max(maxx,a[i]+a[i+2]+1);
			if(a[i-1]==1) maxx=max(maxx,a[i]+a[i-2]+1);
			if(a[i+1]!=1&&a[i-1]!=1) maxx=max(maxx,a[i]+1);
		}
		c=!c;
	}
	cout<<maxx<<'\n';
	
	return 0;
}

```

---

## 作者：wuyouawa (赞：0)

### 题目大意

某城市有大量的历史天气数据。数据中的每一天都被列为有阳光的一天或有降水的一天。某人有兴趣找到连续日照天数最多的记录。不幸的是，一天的数据是不正确的，但他不知道这是哪一天。
你的工作是帮助他确定连续日照的最大可能天数。

### 思路

首先预处理从左边开始的连续晴天天数与从右边开始的连续晴天天数，接着我们把循环扫一遍，看改动哪个数据可以最大化晴天天数，这里的计算可以用预处理的结果，最后输出即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ml[500005],mr[500005],c,ma;
char s[105];
int main(){
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
	}
	for(int i=0;i<n;i++)
	{
		if(s[i]=='S')  c++;
		else  c=0;
		ml[i]=c;
	}
	for(int i=n-1;i>=0;i--)
	{
		if(s[i]=='S')  c++;
		else  c=0;
		mr[i]=c;
	}
	
	for(int i=0;i<n;i++)
	{
		if(s[i]=='S')  
		{
			if(i>0)  
			{
				if(i<n-1)  c=ml[i-1]+mr[i+1];
				else  c=ml[i-1];
			}
			else
			{
				c=mr[i+1];
			}
		}
		else
		{
			if(i>0&&i<n-1) 
			{
				c=ml[i-1]+1+mr[i+1];
			}
			else  if(i==0)
			{
				c=1+mr[i+1];
			}
			else
			{
				c=1+mr[i-1];
			}
		}
		ma=max(ma,c);
	}
	cout<<ma;
	return 0;
} 
```

---

## 作者：banglee (赞：0)

### P12612 [CCC 2025 Junior] Sunny Days 题解
[题目传送门](https://www.luogu.com.cn/problem/P12612)

## 思路
考虑预处理两个数组 $len_l$ 和 $len_r$，分别表示以第 $i$ 天结尾和以第 $i$ 天开头的最长连续晴天长度。

遍历每一天，如果是降水日，则计算将其改为晴天后能连接左右两段晴天的总长度，更新最大值。

但这样你会错两个点，为什么呢？将数据下载下来之后，发现输入都是 S，没有其他的字母，而我们的代码没有特判到这种情况。因此需要加入特判。

如果所有天都是晴天，那么必须修改其中一天为降水日，此时最长连续晴天为 $n-1$。

如果所有天都是降水日，那么修改其中一天为晴天，此时最长连续晴天为 $1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,maxs,llen[500005],rlen[500005];
bool alls=true,allp=true;
char a[500005];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
		if (a[i]=='P') alls=false;
		if (a[i]=='S') allp=false;
	}
    if (alls) {
		cout<<n-1;
		return 0;
	}
	if (allp) {
		cout<<1;
		return 0;
	}
	for (int i=1;i<=n;i++) {
		if (a[i]=='S') llen[i]=llen[i-1]+1;
		else llen[i]=0;
	}
	for (int i=n;i>=1;i--) {
		if (a[i]=='S') rlen[i]=rlen[i+1]+1;
		else rlen[i]=0;
	}
	for (int i=1;i<=n;i++)
		if (a[i]=='S') maxs=max(maxs,llen[i]);
	int ans=maxs;
	for (int i=1;i<=n;i++)
		if (a[i]=='P') {
			int cur=0;
			if (i>0) cur+=llen[i-1];
			if (i<n) cur+=rlen[i+1];
			ans=max(ans,++cur);
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

注意题目中是**恰好一天**记错了。所以如果每天都是晴天我们要将天数减一。

遍历每一天，记录下当前“到现在都没记错”和“已经记错过了”的连续晴天数 $s_0$ 和 $s_1$，如果当天是晴天，那么两个变量都加 $1$；否则更新“到现在都没记错”和“已经记错过了”的最大连续晴天数 $mx_0$ 和 $mx_1$，并使 $s_1\leftarrow s_0+1$，然后将 $s_0$ 赋零。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+2;

int main(){
	int n;cin>>n;
    int s0=0,s1=0,mx0=0,mx1=0;bool p=0;
    for(int i=1; i<=n; i++){
        char c;cin>>c;
        if(c=='S') s0++,s1++;
        else{
            p=1;
            mx0=max(s0,mx0);
            mx1=max(s1,mx1);
            s1=s0+1;
            s0=0;
        }
    }
    mx0=max(s0,mx0);
    mx1=max(s1,mx1);
    int ans=max(mx0,mx1);
    if(!p) ans--;
    cout<<ans;
	return 0;
}
```

---

## 作者：jyh8221 (赞：0)

## 解法

贪心地想，记错晴天无法对答案产生贡献，所以最终答案一定是记错雨天或没记错时。

设 $dp_{i,j} \ (j\in{0,1})$ 表示以第 $i$ 天截止时记错了 $j$ 次雨天产生的最大答案。

即：
$$

{dp}_{i,0} = 
\begin{cases} 
0 & \text{当 } s_i = \texttt{P} \\
{dp}_{i-1,0} + 1 & \text{其余情况}
\end{cases}
$$

$$

{dp}_{i,1} = 
\begin{cases} 
{dp}_{i-1,0} + 1 & \text{当 } s_i = \texttt{P} \\
{dp}_{i-1,1} + 1 & \text{其余情况}
\end{cases}

$$

答案为所有 $dp_{i,1}$ 的最大值。

注意特判 $s$ 中只有 `S`（输出 $n-1$）和 $s$ 中只有 `P`（输出 $1$）的情况。

~注意大小写。~

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[500010][2];
int main() {
    int n;
    cin >> n;
    string s = " ";
    bool hs = 0, hp = 0;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        s += c;
        hs |= (c == 'S');
        hp |= (c == 'P');
    }
    if (hs == 0) {
        cout << 1 << endl;
    }
    else if (hp == 0) {
        cout << n - 1 << endl;
    }
    else {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = (s[i] == 'P' ? 0 : dp[i - 1][0] + 1);
            dp[i][1] = (s[i] == 'P' ? dp[i - 1][0] + 1 : dp[i - 1][1] + 1);
            ans = max({ans, dp[i][1]});
        }
        cout << ans;
    }
}
```

---

