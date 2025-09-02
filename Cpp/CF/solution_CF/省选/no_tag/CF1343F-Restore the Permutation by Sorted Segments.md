# Restore the Permutation by Sorted Segments

## 题目描述

We guessed a permutation $ p $ consisting of $ n $ integers. The permutation of length $ n $ is the array of length $ n $ where each element from $ 1 $ to $ n $ appears exactly once. This permutation is a secret for you.

For each position $ r $ from $ 2 $ to $ n $ we chose some other index $ l $ ( $ l < r $ ) and gave you the segment $ p_l, p_{l + 1}, \dots, p_r $ in sorted order (i.e. we rearranged the elements of this segment in a way that the elements of this segment are sorted). Thus, you are given exactly $ n-1 $ segments of the initial permutation but elements inside each segment are sorted. The segments are given to you in random order.

For example, if the secret permutation is $ p=[3, 1, 4, 6, 2,       5] $ then the possible given set of segments can be:

- $ [2, 5, 6] $
- $ [4, 6] $
- $ [1, 3, 4] $
- $ [1, 3] $
- $ [1, 2, 4, 6] $

Your task is to find any suitable permutation (i.e. any permutation corresponding to the given input data). It is guaranteed that the input data corresponds to some permutation (i.e. such permutation exists).

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
6
3 2 5 6
2 4 6
3 1 3 4
2 1 3
4 1 2 4 6
5
2 2 3
2 1 2
2 1 4
2 4 5
7
3 1 2 6
4 1 3 5 6
2 1 2
3 4 5 7
6 1 2 3 4 5 6
3 1 3 6
2
2 1 2
5
2 2 5
3 2 3 5
4 2 3 4 5
5 1 2 3 4 5```

### 输出

```
3 1 4 6 2 5 
3 2 1 4 5 
2 1 6 3 5 4 7 
1 2 
2 5 3 4 1 ```

# 题解

## 作者：SFlyer (赞：3)

聪明题目，我很喜欢。

考虑到给的 $k_i\ge 2$ 比较可爱，肯定暗藏玄机。

因为数据范围很小，先枚举 $a_1$。首先，如果我们 $a_1$ 固定了，因为一定出现过 $[1,2]$ 这个区间，所以在所有的给定的区间内把所有 $a_1$ 去掉以后，$[1,2]$ 这个区间就只剩下 $a_2$ 这个数。而且因为那个可爱的性质，如果是合法的，有且只有一个区间只剩下一个数。

思路是，知道了 $a_1\sim a_{i-1}$，推断 $a_i$。发现把 $a_1\sim a_{i-1}$ 在所有区间内全部删掉就确定了 $a_i$。

因此我们只要枚举 $a_1$ 然后已知往后推就可以了。记得推出来的 $a$ 不一定合法，还要再检查一下。

最后，我们用 set 维护就可以做到 $\mathcal{O}(n^3\log n)$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e2+2;

int n,k[N],a[N],vis[N][N],mk[N];
set<int> s[N],_s[N];

bool chk(){
	for (int i=2; i<=n; i++){
		set<int> st;
		for (int j=i-(int)_s[mk[i]].size()+1; j<=i; j++){
			st.insert(a[j]);
		}
		if (st!=_s[mk[i]]) return 0;
	}
	return 1;
}

bool cal(){
	for (int i=2; i<=n; i++){
		int pos=-1;
		for (int j=2; j<=n; j++){
			if (vis[j][a[i-1]]) s[j].erase(a[i-1]);
			if (s[j].size()==1){
				if (pos!=-1) return 0;
				pos=j;
			}
		}
		if (pos==-1) return 0;
		a[i]=(*s[pos].begin());
		mk[i]=pos;
	}
	return chk();
}

void solve(){
	cin>>n;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++) vis[i][j]=0;
	}
	for (int i=2; i<=n; i++){
		_s[i].clear();
		cin>>k[i];
		for (int j=1; j<=k[i]; j++){
			int x;
			cin>>x;
			_s[i].insert(x);
			vis[i][x]=1;
		}
	}
	for (int f=1; f<=n; f++){
		for (int i=2; i<=n; i++){
			s[i]=_s[i];
		}
		a[1]=f;
		int fl=cal();
		if (fl){
			for (int i=1; i<=n; i++){
				cout<<a[i]<<" ";
			}
			cout<<"\n";
			return;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：ruo_bot (赞：2)

好像踩标了（？

提供一种 $O(n^2)$ 的做法，考虑最后一个数必然出现且仅出现一次，而第一个数至少出现一次，其余的数出现至少两次，所以如果仅有一个数出现一次，就直接放到最后，并删掉一次与它相关的那一条线段里的数。

而当有两个数出现一次时，我们可以枚举哪个在第一位，并保留这个数直到最后。

如果这个数不是第一个数，可能会导致某一次除了这个数以外没有出现一次的数，或者最后在验证时出现问题，就直接把另一个数放在第一位就好了。

快速维护加入删除数查大小查最后一个数可以用一边记录大小一边记录异或值的方式 $O(1)$ 实现。

于是有了 $O(n^2)$ 的做法。

---

## 作者：K_Madoka (赞：1)

## 题意

给你一个长度为 $n$ 的排列 $a$，但你不知道这个排列具体长什么样，再给出 $n-1$ 个子排列，每个排列的元素为 $[a_l,a_l+1,\dots,a_r]$，$r$ 代表从 $2$ ~ $n$ 的数字，这 $n-1$ 个排列中每个数必将出现一次，现在让你倒推回去，输出一种可能方案的 $a$。**题目保证肯定有一种可行方案。**

首先要了解几个重要的性质：

- 如果一个数出现在所有子排列中出现两次及以上，则这个数肯定不是原排列里的最后一个数
- 如果有一个数出现次数只有一次，则它可能是最后一个也可能是第一个数

知道这么多差不多就可以做这道题了（在这个解法中好像没怎么体现出

## 思路

我们考虑从前往后构造原排列
如果知道了第一位的数，那么就可以通过枚举求出第二位置的，以此类推。

```cpp
const ll MAXN=210;
ll t,n;
ll a[MAXN][MAXN],pos[MAXN],ans[MAXN];
bool ok(){
	for(int now=2;now<=n;now++){//从第二位开始枚举
		for(int i=1;i<n;i++){//枚举子排序
			ll r=a[i][0],x=-1;//r为当前子排序的k
			for(int k=1;k<=a[i][0];k++){
				ll b=a[i][k];//当前子排序的数
				if(!pos[b])x=b;
				else if(pos[b]>=now-a[i][0]+1)r--;//要在当前子排序中
			}
			if(r==1&&x!=-1){//r-1个数都用掉了
				ans[now]=x;
				pos[x]=now;
				break;
			}
		}
		if(ans[now]==0)return false;
	}
	return true;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>a[i][0];//输进来的k
			for(int j=1;j<=a[i][0];j++)cin>>a[i][j];
		}
		for(int i=1;i<=n;i++){//第一位1~n枚举
			for(int j=1;j<=n;j++){
				pos[j]=0;ans[j]=0;//初始化
			}
			ans[1]=i;//枚举的第一位，所以第一位设i
			pos[i]=1;//i的位置为1
			if(ok())break;//可行方案
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<endl;
	}
}
```

参考：

[1](https://blog.csdn.net/mrcrack/article/details/105708055)

[2](https://blog.csdn.net/qq_42937891/article/details/105716624)




---

## 作者：StayAlone (赞：0)

发现自己写得还比较优美？于是来写一份题解。

----------

考虑枚举 $a_1$，由于一定会告知区间 $[1, 2]$，可以确定 $a_2$。接下来继续考虑告知的信息，考虑以 $3$ 为右端点的区间是哪个。若存在一个长度为 $3$ 的区间，含有 $a_1,a_2$，则该区间以 $3$ 为右端点，确定 $a_3$；或者，存在一个长度为 $2$ 的区间，含有 $a_2$，则该区间以 $3$ 为右端点，同样确定 $a_3$。其他情况都一定不是以 $3$ 为右端点的区间，且上述的两种情况不可能同时发生（否则该 $a_1$ 无解）。

推广之。假设已经求出 $a_{1\sim i-1}$，试图求出 $a_i$。一个长度为 $len$ 的区间以 $i$ 为右端点，当且仅当其中有 $len-1$ 个数是 $a_{i-len+1\sim i-1}$，且剩下的那个数未出现过。把剩下的那个数定作 $a_i$ 即可。为避免错误，定下 $a_i$ 时要将这个以 $i$ 为右端点的区间删去，后续不再考虑该区间。

时间复杂度允许我们枚举长度。

按照如上过程，找到解就是合法解，否则枚举下一个 $a_1$。

使用 bitset 实现，$200$ 个数不过是 $4$ 个 ull，可视作常数。时间复杂度 $\mathcal O(n^3)$，具体可看代码。

```cpp
int n, ans[210];
vector <bitset <210>> st[210], now[210];

il bool check(int k) {
    ans[1] = k;
    rep1(i, 1, n) now[i] = st[i];
    rep1(i, 2, n) {
        bool flg = 0; bitset <210> shd;
        rep1(len, 2, i) {
            shd.flip(ans[i - len + 1]);
            for (auto w : now[len]) if ((shd & w) == shd) {
                flg = 1; int k = (shd ^ w)._Find_first();
                ans[i] = k; now[len].erase(find(begin(now[len]), end(now[len]), w));
                break;
            }
            if (flg) break;
        }
        if (!flg) return false;
    } return true;
}

il void solve() {
    read(n);
    rep1(i, 1, n) st[i].clear();
    rep1(i, 2, n) {
        bitset <210> now; int l = read();
        rep1(_, 1, l) now.flip(read());
        st[l].eb(now);
    }
    rep1(i, 1, n) if (check(i)) {
        rep1(j, 1, n) printf("%d ", ans[j]); puts("");
        return;
    }
}

int main() {
    for (int T = read(); T--; ) solve();
    return 0;
}
```

---

## 作者：Shunpower (赞：0)

我真不理解为什么这题很难。

--------------

注意到题面里面的关键事实：所有区间的 $r$ 互不相同且 $l<r$，这启发我们考虑 $l=1,r=2$，我们可以通过枚举来确定前两个数。

然后考虑接下来第三个数怎么办。可以发现接下来所有 $r>3$ 的集合都会剩下至少两个数没有出现，偏偏只有 $r=3$ 的那个集合只剩一个数没有出现，所以我们就能把 $a_3$ 找出来。进一步地，我们可以用类似的方法平推所有数。

但是这样找到的 $a$ 不一定是答案，因为我们实际上并没有保证出现的所有数构成一个区间，这样在限制对前面的数比较弱的时候就会完蛋（比如第一个样例，我们也可以如此增量构造出 $1,3,4,6,2,5$，这主要是 $r=4$ 处的限制太弱导致的）。

但是考虑我们的答案总能被构造出来，我们只要检验所有生成出来的 $\mathcal O(n)$ 个序列就好了。随便写写就能 $\mathcal O(n^3\log n)$，写写桶哈希即可 $\mathcal O(n^3)$。

```cpp
int tc;
int n;
vector <int> p[N];
vector <int> in[N];
int rem[N];
int a[N];
bool vis[N];
int id;
int who[N];
void add(int x){
	vis[x]=1;
	id=0;
	for(auto i:in[x]){
		rem[i]--;
		if(rem[i]==1){
			// if(id){
			// 	id=0;
			// 	return;
			// }
			// assert(!id);
			id=i;
		}
	}
}
bool test(){
	fr1(_,3,n){
		// cout<<"!"<<id<<endl;
		if(!id) return 0;
		who[_]=id;
		for(auto i:p[id]){
			if(!vis[i]){
				a[_]=i;
				add(i);
				break;
			}
		}
	}
	return 1;
}
bool check(){
	fr1(i,3,n){
		vector <int> lik;
		fr2(j,i,i-(int)p[who[i]].size()+1) lik.pb(a[j]);
		sort(lik.begin(),lik.end());
		if(lik!=p[who[i]]) return 0;
	}
	return 1;
}
void solve(){
	cin>>n;
	fr1(i,1,n) in[i].clear();
	fr1(i,2,n) p[i].clear();
	fr1(i,2,n){
		int x;
		cin>>x;
		p[i].resize(x);
		fr1(j,0,x-1) cin>>p[i][j],in[p[i][j]].pb(i);
	}
	fr1(i,1,n){
		if(p[i].size()==2){
			memset(vis,0,sizeof vis);
			fr1(j,1,n) rem[j]=p[j].size();
			a[1]=p[i][0],a[2]=p[i][1];
			// vis[a[1]]=vis[a[2]]=1;
			add(a[1]),add(a[2]);
			// cout<<a[1]<<" "<<a[2]<<endl;
			if(test()){
				if(check()){
					fr1(i,1,n) cout<<a[i]<<" ";
					cout<<endl;
					return;
				}
			}
			memset(vis,0,sizeof vis);
			fr1(j,1,n) rem[j]=p[j].size();
			a[1]=p[i][1],a[2]=p[i][0];
			// vis[=1;
			// cout<<a[1]<<" "<<a[2]<<endl;
			add(a[1]),add(a[2]);
			if(test()){
				if(check()){
					fr1(i,1,n) cout<<a[i]<<" ";
					cout<<endl;
					return;
				}
			}
		}
	}
	// cout<<endl;
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>tc;
	while(tc--) solve();
	ET;
}
//ALL FOR Zhang Junhao.
```

---

