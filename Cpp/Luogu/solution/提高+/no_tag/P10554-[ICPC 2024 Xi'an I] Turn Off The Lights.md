# [ICPC 2024 Xi'an I] Turn Off The Lights

## 题目描述

Kitty 有 $n^2$ 个灯泡，这些灯泡组成了一个 $n\times n$ 的矩阵。

有一天，Kitty 发现这些灯泡中有些是亮的，有些是灭的。Kitty 想要把它们全部关闭。

为了实现她的目标，Kitty 可以执行三种类型的操作：

- (1) 选择一行，反转这一行的状态。这意味着如果这一行的灯泡是亮的，经过此操作后，它将变为灭的。如果这一行的灯泡是灭的，经过此操作后，它将变为亮的。

- (2) 选择一列，反转这一列的状态。这意味着如果这一列的灯泡是亮的，经过此操作后，它将变为灭的。如果这一列的灯泡是灭的，经过此操作后，它将变为亮的。

- (3) 选择一个灯泡，反转这个灯泡的状态。**这种操作最多只能执行 $k$ 次。**

对于当前状态，帮助 Kitty 在 $3n$ 次操作内实现她的目标。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
2 0
0 1
1 0```

### 输出

```
2
0 2
2 0```

## 样例 #2

### 输入

```
3 1
1 0 0
0 1 0
0 0 1```

### 输出

```
-1```

# 题解

## 作者：Purslane (赞：5)

# Solution

一个神秘做法。显然的操作不受影响。

那么我们本质是：选取一些行或列翻转，使得最后开着的灯的数量 $\le k$。

若 $k<n$，必然有一列被只通过行或列翻转变为全关着。这一列是否翻转已经确定了（只有两种，枚举），那么每一行是否翻转也是确定的。对于其他列，暴力扫一遍翻转还是不翻转更优，使用 `bitset` 加速。

若 $k=n$，那么第一列恰好有一个灯是开着的，枚举这盏灯。

容易发现一共只有 $O(n)$ 种可能的翻转方式，而每次翻转需要 $O(\dfrac{n^2}{\omega})$ 判断。

复杂度 $O(\dfrac{n^3}{\omega})$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,k,a[MAXN][MAXN];
bitset<1001> ver[MAXN],hor[MAXN];
int flg1[MAXN],flg2[MAXN];
void output(void) {
	vector<pair<int,int>> ans;
	ffor(i,1,n) if(flg1[i]) ans.push_back({i,0});
	ffor(i,1,n) if(flg2[i]) ans.push_back({0,i});
	ffor(i,1,n) ffor(j,1,n) if(a[i][j]^flg1[i]^flg2[j]) ans.push_back({i,j});
	cout<<ans.size()<<'\n';
	for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) ffor(j,1,n) cin>>a[i][j];
	ffor(i,1,n) ffor(j,1,n) hor[i][j]=a[i][j],ver[j][i]=a[i][j];
	//把第 i 行清干净 
	ffor(i,1,n) {
		memset(flg1,0,sizeof(flg1)),memset(flg2,0,sizeof(flg2));
		flg1[i]=0;
		bitset<1001> bt;
		ffor(j,1,n) if(a[i][j]) bt[j]=flg2[j]=1;
		int cnt=0;
		ffor(I,1,n) if(i!=I) {
			int sum=(hor[I]^bt).count();
			if(sum<=n-sum) cnt+=sum;
			else cnt+=n-sum,flg1[I]=1;	
		}
		if(cnt<=k) return output(),0;
		flg1[i]=1;
		ffor(j,1,n) if(a[i][j]) bt[j]=flg2[j]=0; else bt[j]=flg2[j]=1;
		cnt=0;
		ffor(I,1,n) if(i!=I) {
			int sum=(hor[I]^bt).count();
			if(sum<=n-sum) cnt+=sum;
			else cnt+=n-sum,flg1[I]=1;	
		}
		if(cnt<=k) return output(),0;
	}
	ffor(j,1,n) {
		memset(flg1,0,sizeof(flg1)),memset(flg2,0,sizeof(flg2));
		flg1[1]=0;
		bitset<1001> bt;
		ffor(J,1,n) if((J==1)^a[1][J]) bt[J]=flg2[J]=1;
		int cnt=1;
		ffor(I,2,n) {
			int sum=(hor[I]^bt).count();
			if(sum<=n-sum) cnt+=sum;
			else cnt+=n-sum,flg1[I]=1;	
		}
		if(cnt<=k) return output(),0;
		flg1[1]=1;
		
		ffor(J,1,n) if((J==1)^a[1][J]) bt[J]=flg2[J]=0; else bt[J]=flg2[J]=1;
		cnt=1;
		ffor(I,2,n) {
			int sum=(hor[I]^bt).count();
			if(sum<=n-sum) cnt+=sum;
			else cnt+=n-sum,flg1[I]=1;	
		}
		if(cnt<=k) return output(),0;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：Mr_Az (赞：1)

# [P10554 \[ICPC 2024 Xi'an I\] Turn Off The Lights](https://www.luogu.com.cn/problem/P10554)

**双倍经验：**[**P7315 \[COCI 2018/2019 #3\] Sajam**](https://www.luogu.com.cn/problem/P7315)

两题差别为下表：

| 差别      | P7315 \[COCI 2018/2019 #3] Sajam | P10554 \[ICPC 2024 Xi'an I] Turn Off The Lights |
| ------- | -------------------------------- | ----------------------------------------------- |
| 输出方案    | 不需要                              | 需要                                              |
| $k$ 的范围 | $k \le n$                        | $k < n$                                         |
| 操作次数    | $1，2$ 操作不限制                      | $\le3n$                                         |

快去偷圈！

### Algorithm:

神秘观察 + 构造。

### Solution:

相信你一定做完了双倍经验，那么这道题多了一些限制，但是这个限制其实并没有用：前两个操作至多操作 $n$ 次，第三种操作至多操作 $k$ 次，总共至多操作 $2n+k <3n$，所以这个限制没有用。

其他与双倍经验一样，只不过没有 $k=n$ 的情况。

令 $a_i$ 为第 $i$ 行的**亮灯**情况，$b_i$ 为第 $i$ 行**熄灯**情况，两者互为补集。

对于这道题目，上来是没有头绪的，我们考虑从特殊情况开始思考。

##### $k=0$ 的情况：

此时**不能**单独修改特定格子，容易发现存在**合法**操作方案的条件为**每一行亮灯状况与第一行相同或恰好相反**，$O(N)$ 判断即可。

##### $k < n$ 的情况：

此时**可以**修改一些格子，**但是由于鸽巢原理，总有一行是没有被修改的**。注意到这个之后，我们只需要枚举**每一行作为没有被修改的**。设当前枚举第 $i$ 行，仿照 $k=0$ 时候的方法进行判断，将每一行与 $a_i$ 或 $b_i$ 取异或，这样可以找出来他们与第 $i$ 行**不同的位置个数**，对 $b_i$ 取异或的目的是这一行可以通过题目中的 $1$ 操作进行取反。如果不同的位数 $\le k$ 那么存在合法解。

这道题目需要记录下来操作的位置，开个 `vector` 记录一下即可。

时间复杂度：直接暴力 $O(N^3)$，但是我们有 `bitset`！所以可以优化为 $O(\frac{N^3}{\omega})$。

### Code:

```cpp
namespace Mr_Az{
	int T=1;
	const int N=1008;
	int n,k;
	bitset<N> a[N],t;
	vector<pii> op;
	inline void solve(){
		read(n,k);
		for(rint i=1;i<=n;i++){
			for(rint j=1,x;j<=n;j++){
				read(x);
				a[i][j]=x;
			}
		}
		for(rint i=1;i<=n;i++) t[i]=1;
		for(rint i=1;i<=n;i++){
			int cnt=0;
			for(rint j=1;j<=n;j++) cnt+=min((a[i]^a[j]).count(),(a[i]^t^a[j]).count());
			if(cnt<=k){
				for(rint j=1;j<=n;j++) if(a[i][j]==1) op.eb(0,j);
				for(rint j=1;j<=n;j++){
					if((a[i]^a[j]).count()>(a[i]^t^a[j]).count()){
						a[j]^=t;
						op.eb(j,0);
					}
					for(rint k=1;k<=n;k++) if(a[i][k]!=a[j][k]) op.eb(j,k);
				}
				printf("%u\n",op.size());
				for(auto [x,y]:op) printf("%lld %lld\n",x,y);
				return ;
			}
		}
		puts("-1");
		return ;
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

---

## 作者：fish_love_cat (赞：0)

想出来一半然后不会了 /kel

---

手玩发现不用操作三可以做到令每一行间要么完全不同，要么完全相同。

注意到 $k\le n$，所以合法局面一定可以转化为两种情况：

 1. 当 $k\le n$，存在一行没有亮着的灯。

 2. 当 $k=n$，除上面一种情况外，还可能每行都有一个亮着的灯。

局面 1 是好做的，我们只需要枚举每一行钦定其无灯，然后取使其合法的最小代价即可。

然后我不会做局面 2 了 /qd

但是想到这里你可以先去把 [P10554](https://www.luogu.com.cn/problem/P10554) 过了，那题保证 $k<n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<1005>a[1005];
int ans=1e9;
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        char c;
        cin>>c;
        // a[i][j]=c=='o';
        a[i][j]=c=='1';
    }
    for(int i=1,sum=0;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            bitset<1005>flc(a[i]^a[j]);
            sum+=min(n-(int)flc.count(),(int)flc.count());
        }
        ans=min(ans,sum),sum=0;
        //下面输出方案
        if(ans<=k){
            vector<pair<int,int> >ans;
            for(int j=1;j<=n;j++){
                if(i==j)continue;
                bitset<1005>flc(a[i]^a[j]);
                if(n-(int)flc.count()<(int)flc.count()){
                    for(int g=1;g<=n;g++)
                    if(a[j][g]==a[i][g])ans.push_back(make_pair(j,g));
                    ans.push_back(make_pair(j,0));
                }else{
                    for(int g=1;g<=n;g++)
                    if(a[j][g]!=a[i][g])ans.push_back(make_pair(j,g));
                }
            }
            for(int j=1;j<=n;j++)
            if(a[i][j])
            ans.push_back(make_pair(0,j));
            cout<<ans.size()<<'\n';
            for(int i=0;i<ans.size();i++)
            cout<<ans[i].first<<' '<<ans[i].second<<'\n';
            return 0;
        }
    }
    // puts(ans<=k?"DA":"NE");
    puts("-1");
    return 0;
}
```

接下来是 [P7315](https://www.luogu.com.cn/problem/P7315) 需要考虑的，大神们可以跳过了。

返回局面 2，我们可以钦定第一行的某一位亮着，然后对其操作 3 转变回局面 1，然后直接做就行了。

由于行的顺序无关，所以操作非第一行的相同位与直接对第一行做是等价的，于是不用考虑其他情况了。

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<1005>a[1005];
int ans=1e9;
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        char c;
        cin>>c;
        a[i][j]=c=='o';
    }
    for(int i=1,sum=0;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            bitset<1005>flc(a[i]^a[j]);
            sum+=min(n-(int)flc.count(),(int)flc.count());
        }
        ans=min(ans,sum),sum=0;
    }
    for(int i=1,sum=1;i<=n&&k==n;i++){
        bitset<1005>flc(a[1]);
        if(flc[i])flc[i]=0;
        else flc[i]=1;
        for(int j=2;j<=n;j++){
            bitset<1005>clf(flc^a[j]);
            sum+=min(n-(int)clf.count(),(int)clf.count());
        }
        ans=min(ans,sum),sum=1;
    }
    puts(ans<=k?"DA":"NE");
    return 0;
}
```

---

