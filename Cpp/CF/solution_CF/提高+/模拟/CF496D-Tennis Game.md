# Tennis Game

## 题目描述

【题面描述】

$1$ 玩家和 $2$ 玩家打球。一场比赛分为好多局，每场比赛两人分数从 $0$ 记起，每赢一球就得一分。这一场比赛还有用来记录的序列。每一球如果 $1$ 玩家赢球，裁判就会写下 $1$，如果 $2$ 玩家赢球，裁判就会写下 $2$。

如果在一局中有人率先得到了 $t$ 分，他就赢下了这一局，这一局立马结束。如果在整场比赛中有人赢了 $s$ 局，他就赢下了这场比赛，比赛立马结束。

现在我们知道裁判记录下的序列，但不知道具体的 $s,t$，也不知道每一局比赛在序列上如何划分。现在就问你有多少种可能的 $s,t$，并输出。

## 样例 #1

### 输入

```
5
1 2 1 2 1
```

### 输出

```
2
1 3
3 1
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
3
1 4
2 2
4 1
```

## 样例 #3

### 输入

```
4
1 2 1 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
8
2 1 2 1 1 1 1 1
```

### 输出

```
3
1 6
2 3
6 1
```

# 题解

## 作者：Dehydration (赞：1)

### 前言：

链接附上：[来自](https://blog.csdn.net/walk_upon/article/details/42004323)，[题目](https://www.luogu.com.cn/problem/CF496D)，[我的博客](https://www.luogu.com.cn/blog/661534/)。

### 思路：

1. 枚举 $t$。$t$ 确定了，比赛的全部过程就全都确定了，能否可行以及 $s$ 就都知道了。
2. 已知 $t$ 的话，找下一个 set 的时候用二分，不然 $O(n)$ 的走会超时。已知第 $i$ 个 set 的结束位置 $fr$，找第 $i+1$ 个 set 的结束位置 $to$，那么就找最左边的 $to$，使得 $[fr+1,to]$ 有一个人赢了 $t$ 个 $serve$。如果最后那个 set 结束位置不是 $n$ 肯定不行。
3. 现在已知 $t$，和整场比赛两个人分别赢的 set 的次数。看是否赢 set 最多的人和 $a_n$ 是同一个人。是的话这个 $t$，$s$ 对是 OK 的。否则是不 OK 的。

### 代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=10010; 
int a[N];
int one[N];//前i个有几个1
int two[N];//前i个有几个2
struct point{//最后的答案，最后排序后输出
    int x, y;
}p[N];
int n, ans;
 
bool cmp(point a, point b){
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}
 
void upd(int i, int id, int xx, int yy, int y0){
    if(i == n && a[n] == id && yy > y0){
        //最后赢的人a[n]，一定是结果赢的人。结果赢的人，一定是a[n]
        p[ans].x = xx;
        p[ans++].y = yy;
    }
}
 
int mid_find(int t, int fr, int to){//二分
    if(one[to] - one[fr] < t && two[to] - two[fr] < t) return to + 1;
    int L = fr + 1, R = to;
    while(L < R){
        int M = (L + R) >> 1;
        int t1 = one[M] - one[fr];
        int t2 = two[M] - two[fr];
        if(t1 < t && t2 < t) L = M + 1;
        else if(t1 > t || t2 > t) R = M - 1;
        else if(t1 == t && t2 == t) R = M - 1;
        else if(t1 == t) {
            if(a[M] == 1) return M;
            else R = M - 1;
        }
        else{
            if(a[M] == 2) return M;
            else R = M - 1;
        }
    }
    return L;
}
 
void check(int t){
    int num1 = 0, num2 = 0;
    int win1 = 0, win2 = 0;
    for(int i = 0; i < n; ){
        int ii = mid_find(t, i, n);//第i+1到第ii个是一场比赛，赢的人赢了t局
        if(ii > n) return ;
        num1 = one[ii] - one[i];
        num2 = two[ii] - two[i];
        if(num1 == t) {
            ++win1;
            upd(ii, 1, t, win1, win2);
        }
        else if(num2 == t){
            ++win2;
            upd(ii, 2, t, win2, win1);
        }
        i = ii;
    }
}
 
int main(){
    while(scanf("%d", &n) != EOF){
        one[0] = 0;
        two[0] = 0;
        int m = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            if(a[i] == 1) {
                ++m;
                one[i] = one[i - 1] + 1;
                two[i] = two[i - 1];
            } else {
                one[i] = one[i - 1];
                two[i] = two[i - 1] + 1;
            }
        }
        if(a[n] == 2) m = n - m;
        ans = 0;
        for(int i = 1; i <= m; ++i){
            check(i);
        }
        printf("%d\n", ans);
        sort(p, p + ans, cmp);
        for(int i = 0; i < ans; ++i) printf("%d %d\n", p[i].y, p[i].x);
    }
    return 0;
}
```

---

## 作者：在想Peach (赞：1)

我们从 $1$ 到 $n$ 枚举 $t$ ，然后发现对于每个 $t$ 仅对应一个 $s$ 。

对于每个 $t$ ，我们从头暴力跳，每次找到第一个 $1$ 或者 $2$ 满足 $t$ 的点跳过去，这个可以用 二分 + 前缀和 实现。
 
此时发现每次至少会跳 $i$ 格，也就是说每次枚举跳的步数分别至多是   $\frac{n}{1}$ , $\frac{n}{2}$, $\frac{n}{3}$, $\frac{n}{4}$ ..... $\frac{n}{n}$ 的

这是一个调和级数，复杂度是 $O(n\log_2n)$ 的

加上二分，代码复杂度为 $O(n \log^2 n)$ 。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#define int long long
using namespace std;
const int maxn=100005;
struct node{
	int s,t;
	friend bool operator <(node a,node b){
		if(a.s!=b.s)return a.s<b.s;
		return a.t<b.t;
	}
}g[maxn];
int T,n,a[maxn],sum1[maxn],sum2[maxn];
int tot=0;
int read(){
	char z=getchar();int x=0,y=1;
	while(z<'0'||z>'9'){if(z=='-')y=-1;z=getchar();}
	while(z<='9'&&z>='0'){x=x*10+z-'0';z=getchar();}
	return x*y;
}
void init(){
	n=read();
	sum1[0]=sum2[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum1[i]=sum1[i-1];
		sum2[i]=sum2[i-1];
		if(a[i]==1)sum1[i]++;
		else sum2[i]++;
	}
	sum1[n+1]=sum1[n];
	sum2[n+1]=sum2[n];
}
bool check(int u,int l,int r){
	if(sum1[r]-sum1[l-1]>=u)return 1;
	if(sum2[r]-sum2[l-1]>=u)return 1;
	return 0;
}
void solve(){
	for(int i=1;i<=n;i++){
		int now=1;
		int win1=0,win2=0;int op=0;
		while(1){
			int l=now,r=n+1;
			while(l<r){
				int mid=(l+r)>>1;
				if(!check(i,now,mid))l=mid+1;
				else r=mid;
			}
			if(sum1[l]-sum1[now-1]>=i)win1++,op=1;
			else win2++,op=2;
			if(l==n+1)break;
			if(l==n){if((op==1&&win1>win2)||(op==2&&win2>win1)){g[++tot].s=max(win1,win2);g[tot].t=i;}break;}
			now=l+1;
		}
	}
	cout<<tot<<endl;
	sort(g+1,g+tot+1);
	for(int i=1;i<=tot;i++)cout<<g[i].s<<" "<<g[i].t<<endl;
}
signed main(){
	init();
	solve();
	return 0;
}
```


---

