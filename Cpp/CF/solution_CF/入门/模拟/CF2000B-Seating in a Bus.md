# Seating in a Bus

## 题目描述

有 $n$ 个数，编号分别为 $1$ 到 $n$。必须按以下规则来标记这些数：

- 若没有数被标记，则被标记的数可以是任何从 $1$ 到 $n$ 的数。
- 否则，被标记的数至少有一个与它相邻的数被标记。具体的，如果要标记编号 $i$，则编号 $i-1$ 和 $i+1$ 至少有一个被标记。

现在，这 $n$ 个数都要被标记，用数组 $a$ 来表示依次要标记那些数。具体的，$a_1$ 表示第一个要标记的数，$a_2$ 表示第二个要标记的数，依次类推。

你已经知道了 $a$ 数组的内容，要求是否满足规则。

例如 $n=5$，且 $a$ = [$5，4，2，1，3$]，则不满足要求，因为 $a_3$ 中被标记的数是 $2$，而编号 $1$ 和 $3$ 却都没有被标记。

## 样例 #1

### 输入

```
4
5
5 4 2 1 3
3
2 3 1
4
2 3 1 4
5
1 2 3 5 4```

### 输出

```
NO
YES
YES
NO```

# 题解

## 作者：Takanashi__Hoshino (赞：4)

## 题意

给你一个公交车，上面有 $n$ 个座位，编号 $1\sim n$，同时又有 $n$ 个乘客来坐车，乘客选座需要遵守以下规则：

1. 若车上没有任何乘客，则随意选座。
2. 若车上已经有乘客了，则上车的乘客需要挨着之前上车的乘客坐下。即对于第 $i$ 个座位，需要第 $i+1$ 或第 $i-1$ 个座位上有人才能坐在第 $i$ 个座位上，$i\in [1,n]$。

你需要判断是不是所有乘客都遵守了规则。
## 分析

简单模拟题，我的思路是使用一个数组 $cnt$。$cnt_i$ 表示第 $i$ 个座位旁边的人的个数。若 $cnt_i=0$ 则表示第 $i$ 个座位旁边的第 $i-1$ 和第 $i+1$ 个座位都没有人。那么代码就很显然了。

## CODE


```cpp
int n,t,x,cnt[200005];
bool f;
int main(){
	t=read();
	while(t--){
		f=1;//这里指的是当前数据组是否输出，而不是指数据是否满足题意。
		memset(cnt,0,sizeof(cnt));
		n=read();
		for(int i=1;i<=n;i++){
			x=read();
			if(cnt[x]<1&&f&&i!=1){//第一个人肯定随便坐的。
				puts("NO");
				f=0;//我是在线读入，所以不能直接退出循环。
//退出循环会导致读不完数据，进而导致读入下一组数据时出错。
//为什么要设置记录输出的变量是因为有可能有多名乘客都没有遵守规则，不设置的话会输出很多 NO。
			}
			cnt[x+1]++;
			cnt[x-1]++;
		}
		if(f)puts("YES");//若从始至终都没有输出，那肯定就是都遵守了规则。
	}
	return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

直接模拟即可。

第一个人直接标记，其余就看旁边有没有人就行了，如果都没人那直接判 NO。

**注意**桶要清空 $0\sim n+1$。

[代码](//codeforces.com/contest/2000/submission/276137335)。

---

## 作者：_dbq_ (赞：0)

## 前言
还没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF2000B)或[这里](https://codeforces.com/problemset/problem/2000/B)读题。

本题所用知识点：**模拟**、**桶**。

## 思路
题目按照顺序给出每个人的座位，第一个人由于车是空的可以随便做。

接下来我们对每个人的座位进行判断，利用桶判断左右是否有人。有人则在桶上的这个位置打标记，否则输出 `NO`。

多组数据，**桶要清空**。

## 代码

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
cint N=2e5+10;
int a[N];//桶
inline LL read(){//快读
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve()
{
    bool flag=true;
    cint n=read();
    for(int i=1;i<=n;i++)
    {
        cint x=read();
        if(i!=1)
        {
            if(a[x-1]!=1&&a[x+1]!=1) flag=false;//判左右有没有人
        }
        a[x]=1;//打标记
    }
    if(flag) cout<<"YES";
    else cout<<"NO";
    cout<<'\n';
    memset(a,0,sizeof(a));//清空
}
int main()
{
    #ifdef dbq
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T=read();
    while(T--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## CF2000B Seating in a Bus 题解

### 题意
有 $n$ 名乘客上车，第一个人可以随便坐，后面的人只能坐在旁边有人的座位。问是否所有乘客都遵守了规则。

### 思路
考虑用桶存下每个位置是否有人，如果是第一个人，那么他肯定遵守了规则。后面的人遵守了规则当且仅当桶中相邻的位置为 $1$，否则他违反了规则。如果遵守了规则，那么记录桶中相应位置为 $1$，具体实现详见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
const int maxn=2e5+7;
int a[maxn];
int f[maxn]; 
void solve(){
	int n;
	cin>>n;
	int ff=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(i==1||f[a[i]+1]||f[a[i]-1]){
			f[a[i]]=1;
		}
		else{
			cout<<"no"<<'\n';
			ff=1;
			break;
		}
	}
	if(ff==0) cout<<"yes"<<'\n';
	for(int i=1;i<=n;i++){
		a[i]=0;
		f[i]=0;
	}
}

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}



```

---

## 作者：ybc2026lhy (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/article/qhy0bnvw)

##### 分析：
每次上车都判断一下它选的座位符不符合条件，只要有一个不符合，就输出 NO。否则，标记这个座位已有人，然后继续遍历，如果遍历完了整个序列还没输出 NO，则输出 YES。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	while(T--){
		int n,a[200005]={0},vis[200005]={0};
		bool flag=true;//打标记
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		vis[a[1]]=1;//第一个人随便坐
		for(int i=2;i<=n;i++){
			if(vis[a[i]-1]==0&&vis[a[i]+1]==0){//左右两边没人
				flag=false;
				break;
			} else {//左边或右边有人
				vis[a[i]]=1;
			}
		}
		if(flag==true){
			cout<<"YES"<<"\n";
		} else {
			cout<<"NO"<<"\n";
		}
	}
	return 0;
}

---

## 作者：__O_v_O__ (赞：0)

从前到后枚举每个人，同时维护一个桶表示当前座位是否有人。

考虑枚举到某个人：

- 如果这个人是第一个人，则直接把桶中这个位置设为有人。

- 如果不是，那么判断他的前面和后面是否至少有一个人。如果不是则跳出循环，输出 `NO`，否则把桶中此位置设为有人。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[200005],b[200005],fl;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n,fl=true;
		b[0]=b[n+1]=0;
		for(int i=1;i<=n;i++)cin>>a[i],b[i]=0;
		for(int i=1;i<=n;i++){
			if(i==1)b[a[i]]=1;
			else{
				if(!b[a[i]-1]&&!b[a[i]+1]){
					cout<<"NO\n";
					fl=false;
					break;
				}else{
					b[a[i]]=1;
				}
			}
		}
		if(fl)cout<<"YES\n";
	}return 0;
}
```

---

