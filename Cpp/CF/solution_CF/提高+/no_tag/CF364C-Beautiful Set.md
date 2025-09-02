# Beautiful Set

## 题目描述

We'll call a set of positive integers $ a $ beautiful if the following condition fulfills: for any prime $ p $ , if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF364C/de99426f3fbaa26518074daf10b8f9b390d1a140.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF364C/04ac8a5d83c7f06e74fe73e1ed271d0d74dd42cb.png). In other words, if one number from the set is divisible by prime $ p $ , then at least half of numbers from the set is divisible by $ p $ .

Your task is to find any beautiful set, where the number of elements is equal to $ k $ and each element doesn't exceed $ 2k^{2} $ .

## 样例 #1

### 输入

```
10
```

### 输出

```
16 18 24 27 36 48 54 72 108 144 
```

# 题解

## 作者：Priestess_SLG (赞：0)

真不会做啊呜呜呜呜呜呜呜呜呜

考虑一个简单的构造：给出一个质因子集合 $S$，然后用 $S$ 内的质因数组合出前 $k$ 小的数。但是这样很明显不能保证正确性，于是考虑调整答案：

将集合 $S$ 内所有元素从大到小排序，依次对于每一个质因子 $x$：若 $x$ 在序列中出现的次数不足 $\frac k2$，那么从小到大，给所有不是 $x$ 倍数的数乘以 $x$ 使得其变为 $x$ 的倍数，并保持其余所有数出现次数不变，而 $x$ 的倍数出现次数自增 $1$。因此这个东西只会让每一个质因子出现的次数变多而不会变少，而且不会出现新的质因子，因此可以证明其正确性。

事实证明取 $S=\lbrace2,3,5,7,11\rbrace$ 即可在题目给定条件下通过该题目。因为 $k$ 太小所以直接随便暴力枚举就可以通过该题。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
int a[510][510];

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int k;
    cin >> k;
    set<int> se, se2;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
    for (int i = 2; i <= 2 * k * k; ++i) {
        int j = i;
        while (j % 2 == 0) j /= 2;
        while (j % 3 == 0) j /= 3;
        while (j % 5 == 0) j /= 5;
        while (j % 7 == 0) j /= 7;
        while (j % 11 == 0) j /= 11;
        if (j == 1) {
            se.emplace(i);
            if (i % 2 == 0) ++c1;
            if (i % 3 == 0) ++c2;
            if (i % 5 == 0) ++c3;
            if (i % 7 == 0) ++c4;
            if (i % 11 == 0) ++c5;
            if (se.size() >= k) break;
        }
    }
    se2.clear();
    for (const int &i : se)
        if (i % 11 != 0) se2.emplace(i);
    while (c5 * 2 < k) {
        auto it = se2.begin();
        int val = *it;
        se2.erase(it);
        if (se.find(val * 11) == se.end() && val * 11 <= 2 * k * k) {
            se.erase(se.find(val));
            se.emplace(val * 11);
            ++c5;
        }
    }
    se2.clear();
    for (const int &i : se)
        if (i % 7 != 0) se2.emplace(i);
    while (c4 * 2 < k) {
        auto it = se2.begin();
        int val = *it;
        se2.erase(it);
        if (se.find(val * 7) == se.end() && val * 7 <= 2 * k * k) {
            se.erase(se.find(val));
            se.emplace(val * 7);
            ++c4;
        }
    }
    se2.clear();
    for (const int &i : se)
        if (i % 5 != 0) se2.emplace(i);
    while (c3 * 2 < k) {
        auto it = se2.begin();
        int val = *it;
        se2.erase(it);
        if (se.find(val * 5) == se.end() && val * 5 <= 2 * k * k) {
            se.erase(se.find(val));
            se.emplace(val * 5);
            ++c3;
        }
    }
    se2.clear();
    for (const int &i : se)
        if (i % 3 != 0) se2.emplace(i);
    while (c2 * 2 < k) {
        auto it = se2.begin();
        int val = *it;
        se2.erase(it);
        if (se.find(val * 3) == se.end() && val * 3 <= 2 * k * k) {
            se.erase(se.find(val));
            se.emplace(val * 3);
            ++c2;
        }
    }
    se2.clear();
    for (const int &i : se)
        if (i % 2 != 0) se2.emplace(i);
    while (c1 * 2 < k) {
        auto it = se2.begin();
        int val = *it;
        se2.erase(it);
        if (se.find(val * 2) == se.end() && val * 2 <= 2 * k * k) {
            se.erase(se.find(val));
            se.emplace(val * 2);
            ++c1;
        }
    }
    for (const int &i : se) cout << i << ' ';
    cout << '\n';
    return 0;
}

```

---

## 作者：柳易辰 (赞：0)

令答案集合为 $S$，质因子集合为 $P$。

容易发现，$P$ 应该满足：$|P|$ 尽可能小、$p$ 尽可能小。$|P|$ 尽可能小就可以减少对答案集合的限制，$p$ 尽可能小就可以让 $s$ 尽可能小。

于是我们就可以这样选择质因子集合：$\{2\},\{2,3\},\{2,3,5\},\{2,3,5,7\},\{2,3,5,7,11\}\dots$一个个选择过去，直到可以为止。

假设我们选好了 $P$，我们可以枚举每个数 $i$，如果 $i$ 的所有质因子都 $\in P$，那么就将 $i$ 放入 $S$。但是这样就有一个问题：不一定可以保证 $S$ 中至少有一半的数是 $p$ 的倍数。所以我们可以在 $S$ 生成好后进行调整。调整如下：如果 $S$ 中 $p$ 的倍数小于一半，那么就从小到大遍历每个满足 $i\in S\land p\nmid i\land pi\notin S$ 的数 $i$，把 $i$ 删去，把 $pi$ 放入集合。容易证明，这样调整后一定可以满足条件。

经过尝试，当 $k=5000$ 时，集合取到 $\{2,3,5,7,11\}$ 可以通过。注意调整时，先调整大的质因子，再调整小的质因子可以使 $s$ 中的数可以通过。

[Codeforces AC 记录](https://codeforces.com/contest/364/submission/273047397)。

---

## 作者：是青白呀 (赞：0)

首先，想要满足所有质因数都出现了至少一半，我们需要质因数个数尽量少。同时，质因数大小也应当尽量地小。

仅有质因数 $2$ 的时候，$k=10$ 也无法构造出合适的解。因此我们从质因数集合为 $\{2,3\}$ 开始检查是否有合法解，若有解则直接输出解，无解则将下一个质数加入质因数集合继续判断。

假设当前的质因数集合为 $P$，我们可以轻松求出不超过 $2k^2$ 的所有正整数中，质因数在 $P$ 集合中的数集 $S$。设 $S$ 中含有质因数 $x$ 的子集为 $S_x$。我们需要从大往小枚举每个 $x\in P$，然后进行选择。为了使选出来的数含有尽可能多的质因数，我们将 $S_x$ 中的元素按照质因数个数从大往小排序，然后依次选择（事实上这道题的限制比较宽松，不排序也可以通过）。选择的同时维护一个计数器，一旦当 $S_x$ 中被选择的元素个数超过了一半，就停止选择，开始枚举下一个较小的质因数。直到所有质因数枚举完毕，再选择任意的 $S$ 中未被选择过的数，使得选出来的数的数量达到 $n$ 个。这样即可构造一组合法解。

若在构造过程中，$S_x$ 中的元素不足一半，或总元素数量超过了 $k$，则说明当前质因数集合下不存在合法解，需要继续判断下一个集合是否有解。

为了减少常数，便于判断，我们可以强制钦定 $S_x$ 中的元素只含有不大于 $x$ 的质因数，避免选重。

当 $k=5000$ 时，可以在集合 $P=\{2,3,5,7,11\}$ 中找到一组合法解，因而枚举集合的总次数不会超过 $4$ 次，每次枚举的复杂度为 $O(k^2)$，因而总时间复杂度是可以接受的。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define lowbit(x) x&(-x)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define pb push_back
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=2e6+5,M=1e6+2,mo=1e9+7,inf=1e9+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,upp;
int pri[6]={1,2,3,5,7,11};
int num[6][N],cnt[6];
int exi[N*5],cnte;
int nnum[6];
bool ok=0,vis[50000002];
void add(int x){
	rep(i,1,5)
	    if(x%pri[i]==0)nnum[i]++;
}
void solve(int x){
	int nwn=cnte;
	rep(i,1,nwn){
		int nw=exi[i];
		for(int j=nw*pri[x];j<=upp;j*=pri[x])
		    exi[++cnte]=j,num[x][++cnt[x]]=j;
	}
	rep(i,1,x)
	    nnum[i]=0;
	rep(i,1,upp)
	    vis[i]=0;
	int sum=0;
	repp(i,x,1){//从大往小枚举质因数，选出至少一半
		rep(j,1,cnt[i]){
			add(num[i][j]),vis[num[i][j]]=1,sum++;
			if(nnum[i]>=(n+1)/2)break;
		}
		if(nnum[i]<(n+1)/2)return;
    }
	rep(i,1,x){//补全
		rep(j,1,cnt[i]){
			if(sum>=n)break;
			if(!vis[num[i][j]])vis[num[i][j]]=1,sum++;
		}
		if(sum>=n)break;
	}
	if(sum<n)return;
	rep(i,1,upp)
	    if(vis[i])printf("%d ",i);
	ok=1;
}
int main(){
	read(n),upp=2*n*n;
	for(int i=2;i<=upp;i*=2)
	    exi[++cnte]=i,num[1][++cnt[1]]=i;
	rep(i,2,5)
	    if(!ok)solve(i);
	return 0;
}
```

---

