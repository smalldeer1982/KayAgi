# Robot Program

## 题目描述

在坐标轴上有一个机器人。初始时，机器人位于点 $x$（$x \ne 0$）。机器人有一个长度为 $n$ 的命令序列，由字符组成，其中 L 表示向左移动一个单位（从点 $p$ 移动到点 $(p-1)$），R 表示向右移动一个单位（从点 $p$ 移动到点 $(p+1)$）。

机器人开始执行这个命令序列（每秒执行一个命令，按顺序执行）。然而，每当机器人到达点 0 时，已执行命令的计数器会被重置（即它会从头开始重新执行整个命令序列）。如果机器人完成了所有命令且未处于 0 点，它将停止运行。

你的任务是计算在接下来的 $k$ 秒内，机器人会进入点 0 多少次。

## 说明/提示

第一个示例中，机器人移动路径为：$2 \rightarrow 1 \rightarrow \underline{0} \rightarrow -1 \rightarrow -2 \rightarrow -1$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，点 0 被进入 1 次。

第二个示例中，机器人移动路径为：$-1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1$。机器人运行了 8 秒，点 0 被进入 4 次。

第三个示例中，机器人移动路径为：$-2 \rightarrow -3 \rightarrow -2 \rightarrow -1 \rightarrow \underline{0} \rightarrow -1$。机器人运行了 5 秒，点 0 被进入 1 次。

第四个示例中，机器人移动路径为：$3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 3 \rightarrow 2$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，未到达点 0。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2 6
LLR
2 -1 8
RL
4 -2 5
LRRR
5 3 7
LRRLL
1 1 1
L
3 -1 4846549234412827
RLR```

### 输出

```
1
4
1
0
1
2423274617206414```

# 题解

## 作者：e_mei_mountain_704 (赞：3)

#### CF2070B Robot Program 题解

##### 这道题是一道递推题。先计算从外面走到 $0$ 点，在计算从 $0$ 点走回 $0$ 点的轮回。

---

先是从外面走到 $0$ 点,如果发现走到 $0$ 点了直接结束。

```cpp
for (int i=1; i<=n; i++)
{
    if (s[i]=='L')
  	x--;
  	else x++;
    cnt++;
    if (x==0) break;
}
```

---

然后进行判断。

```cpp
if (x!=0)
{
    cout<<0<<endl;
    continue;
}
```


---

后面的从 $0$ 点走回 $0$ 点和上面的从外面走到 $0$ 点一样，就不展示了。

---

最后进行判断和输出。

```cpp
if (x!=0)
{
    cout<<1<<endl;
    continue;
}
cout<<k/cnt+1<<endl;
```


---

整理加工后就变成了 AC 代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main ()
{
	int t;
	cin>>t;
	while (t--)
	{
		int n,x,k,cnt=0;
		cin>>n>>x>>k;
		string s;
		cin>>s;
		s=' '+s;
		for (int i=1; i<=n; i++)
		{
			if (s[i]=='L')
				x--;
			else x++;
			cnt++;
			if (x==0) break;
		}
		k-=cnt;
		if (x!=0)
		{
			cout<<0<<endl;
			continue;
		}
		cnt=0;
		for (int i=1; i<=n; i++)
		{
			if (s[i]=='L')
				x--;
			else x++;
			cnt++;
			if (x==0) break;
		}
		if (x!=0)
		{
			cout<<1<<endl;
			continue;
		}
		cout<<k/cnt+1<<endl;
	}
    return 0;
}
```
~~各位大佬点个赞再走吧。~~

---

## 作者：shiyilang0910 (赞：2)

## 思路
题目说每次到达 $0$ 就会 **重新执行指令**，询问遇到 $0$ 的次数。首先，执行第一次时我们看能不能到达 $0$ ，如果不能，就结束了，输出 $0$ 。否则，我们想，到达 $0$ 时就会重新开始执行，那么，每次再到达 $0$  时，又会从 $0$ 开始……所以，我们只要判断从 $0$ 开始又到达 $0$ 的距离，如果不能到达或者一次都执行不了，就输出 $1$ 。最后用数学公式计算一下次数就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,x,k,ans=0;
string s;
signed main(){
    cin>>t;
    while(t--){
    	cin>>n>>x>>k;
    	cin>>s;
    	int cnt=-1,xx=x;
        //模拟
    	for(int i=0;i<s.size();i++){
    		if (s[i]=='L'){//操作一下
    			xx--;
			}else{
				xx++;
			}
			if (xx==0){
				cnt=i;
				break;
			}
		}
		if (cnt==-1){//从x到不了0，一次都没有，结束
			cout<<0<<endl;
			continue;
		}
		int cntt=-1;
		xx=0;
        //模拟
		for(int i=0;i<s.size();i++){
			if (s[i]=='L'){//操作一下
				xx--;
			}else{
				xx++;
			}
			if (xx==0){
				cntt=i;
				break;
			}
		}
		if (cntt==-1||cnt+cntt+2>k){//从0到不了0或者一个周期也到不了，只有从x到0的一次，结束
			cout<<1<<endl;
			continue;
		}
		cout<<(k-(cnt+1)/*总长度减去一开始的长度*/)/(cntt+1/*从0到0的周期长度*/)+1/*加上原来的从x到0的一次*/<<endl;
	}
    return 0;//表示完美地结束
}
```

---

## 作者：AstaVenti_ (赞：1)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{46}$ 篇题解。

# $\mathbf{0x01}$ 承

一个机器人初始在 $x$ 位置，会按照指令移动，如果移动到原点会重新执行指令，求 $k$ 秒内经过了几次原点。

# $\mathbf{0x02}$ 转

我们需要记录两个数 $\text{step1}$ 和 $\text{step2}$，分别表示机器人到达原点所需的时间和到达原点之后再次到达原点所需的时间（也就是周期长度）。

在这期间一共经过的周期数量 $\frac{k-\text{step1}}2$，再加上第一次到达原点的时间，答案即为 $1+\frac{k-\text{step1}}2$。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,x,k;
string s;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>k>>s;
		ll nw1=x,nw2=0,stp1=n+1,stp2=k+1;
		s=' '+s;
		for(ll i=1;i<=n;i++){
			if(s[i]=='L')nw1--,nw2--;
			if(s[i]=='R')nw1++,nw2++; 
			if(nw1==0&&stp1==n+1)stp1=i;
			if(nw2==0&&stp2==k+1)stp2=i;
		}
		cout<<((stp1!=n+1&&k>=stp1)?1+(k-stp1)/stp2:0)<<endl;
	}
}

```

---

## 作者：zzldd (赞：1)

题意比较简单，不再赘述。\
注意到机器人的初始位置为 $x$，所以我们需要先对 $s$ 进行遍历，统计当前 $s$ 中字母 L 的数量为 $L$，字母 R 的数量为 $R$，机器人到达点 $0$ 时，即 $L+R+x=0$ 时，使 $k$ 减去当前使用的秒数，更新 $ans$ 值为 $1$，并退出循环。另外，当使用的秒数大于 $k$ 时，应直接退出循环。\
此时，如果 $ans$ 的值不为 $1$，则机器人无法到达点 $0$，直接输出 $0$。\
之后，我们再对 $s$ 进行遍历，统计当前 $s$ 中字母 L 的数量为 $L$，字母 R 的数量为 $R$，当机器人回到点 $0$ 时，即 $L+R=0$ 时，记录当前使用时间为 $sz$，退出循环。\
最终答案即为 $k\div sz+1$。\
如果机器人不能从点 $0$ 走回点 $0$，则应直接输出 $1$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int L,R,T,n,x,k;
string s;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>k;
		cin>>s;L=R=0;int l=s.size(),ans=0;
		for(int i=0;i<l;i++){
			if(s[i]=='L') L--;
			if(s[i]=='R') R++;
			if(i>k) break;
			if(x+L+R==0){
				ans++;
				k-=i+1;
				break;
			}
		}if(ans==0){
			cout<<ans<<"\n";
			continue;
		}L=R=0;int sz=-1;
		for(int i=0;i<l;i++){
			if(s[i]=='L') L--;
			if(s[i]=='R') R++;
			if(L+R==0){
				sz=i+1;
				break;
			}
		}cout<<(sz==-1?1:1+(k/sz))<<"\n";
	}
}

```

---

