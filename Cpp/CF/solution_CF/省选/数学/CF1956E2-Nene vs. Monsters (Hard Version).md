# Nene vs. Monsters (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

Nene is fighting with $ n $ monsters, located in a circle. These monsters are numbered from $ 1 $ to $ n $ , and the $ i $ -th ( $ 1 \le i \le n $ ) monster's current energy level is $ a_i $ .

Since the monsters are too strong, Nene decided to fight with them using the Attack Your Neighbour spell. When Nene uses this spell, the following actions happen in the following order one by one:

- The $ 1 $ -st monster attacks the $ 2 $ -nd monster;
- The $ 2 $ -nd monster attacks the $ 3 $ -rd monster;
- $ \ldots $
- The $ (n-1) $ -th monster attacks the $ n $ -th monster;
- The $ n $ -th monster attacks the $ 1 $ -st monster.

When the monster with energy level $ x $ attacks the monster with the energy level $ y $ , the energy level of the defending monster becomes $ \max(0, y-x) $ (the energy level of the attacking monster remains equal to $ x $ ).

Nene is going to use this spell $ 10^{100} $ times and deal with the monsters that will still have a non-zero energy level herself. She wants you to determine which monsters will have a non-zero energy level once she will use the described spell $ 10^{100} $ times.

## 说明/提示

In the first test case, the following actions happen during the first $ 3 $ uses of the spell in this order:

- Nene uses the Attack Your Neighbour spell for the first time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 5-2)=3 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 3-3)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the second time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 3-2)=1 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-1)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the third time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 1-2)=0 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-0)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ .

After each of the next uses of the spell, energy levels of monsters do not change. Thus, only the $ 1 $ -st monster has a non-zero energy level in the end.

In the second test case, both monsters initially have zero energy level.

## 样例 #1

### 输入

```
5
3
2 5 3
2
0 0
4
1 5 7 2
4
4 2 1 2
13
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
1
1 
0

1
1 
2
1 3 
6
1 3 6 8 10 12```

# 题解

## 作者：ReTF (赞：9)

世界名画：![](https://cdn.luogu.com.cn/upload/image_hosting/mwhro9yu.png) 死因：没开 long long

> 题意：有 $n$ 个排成一圈的人，顺时针标号，第 $i$ 个血量为 $a_i$，从 $1$ 开始顺时针转圈，第 $i$ 个把第 $i+1$ 个的血量变为 $\max\{0,a_{i+1}-a_i\}$，问有哪些人在最后血量非零。

### E1
发现这个操作后面会受到前面的直接影响，难以直接维护，考虑发现题目中的性质。

性质：在操作 $O(\sqrt{w})$ 圈后，最大的非零连通块大小 $\le 2$。其中的 $w=\max\{a_i\}$。

考虑证明。假设在某一个时刻我们有一个大小 $= 3$ 的连通块 $a_i,a_{i+1},a_{i+2}$，$\sqrt{2w}$ 次操作后 $a_{i+1}$ 至少受到 $\sqrt{2w}$ 的伤害，$a_{i+2}$ 至少受到 $w+\dfrac{\sqrt{2w}}{2}$ 的伤害，其血量变为 $0$。

所以我们暴力操作 $650$ 圈，剩下的大小为 $1$ 的非零连通块一定活到最后，大小为 $2$ 的非零连通块一定是顺时针第一个活到最后。
### E2
性质：在操作 $O(\sqrt[3]{w})$ 圈后，最大的非零连通块大小 $\le 3$。其中的 $w=\max\{a_i\}$。证明和 E1 相似。

所以我们暴力操作 $2200$ 圈，剩下的大小 $\le 3$ 的非零连通块的最终结果可以 $O(1)$ 计算。

---

## 作者：SkyLines (赞：6)

## Solution

如果连续四只怪物的血量为 $a_1,a_2,a_3,a_4$，且血量均大于 $0$，在使用 $T$ 次法术后未死亡，则 $a_2$ 至少减少 $O(T)$，$a_3$ 至少减少 $O(T^2)$，即 $(T-1)+(T-2)+ \dots +1$，同理可得 $a_4$ 至少减少 $O(T^3)$。

设 $A=\max_{i=1}^n a_i$，则使用 $O(\sqrt[3]{A})$ 次后，$a_1,a_2,a_3,a_4$ 至少有一只会死亡。所以可以枚举，直到没有连续四只怪物存活。

如果连续四只怪物的血量为 $0,a_1,a_2,a_3$，则 $a_1$ 必永久存活（因为没有怪物能攻击它），$a_2$ 终将死亡（因为 $a_1$ 将永远地攻击它，直到死亡），并对 $a_3$ 造成 $B=(a_2-a_1)+(a_2-2 \times a_1)+ \dots +(a_2 \bmod a_1)$ 的伤害，如果 $a_3 > B$ 时。

时间复杂度：$O(n \times \sqrt[3]{A})$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
const int N = 1e6 + 5;
int n, a[N], cnt, num, ans[N], tmp, tmp2, tmp3, t;
ll tt;
bool check(){
	a[n] = a[0];
	a[n + 1] = a[1];
	a[n + 2] = a[2];
    for(int i = 0; i < n; i++){
		if(a[i] && a[i + 1] && a[i + 2] && a[i + 3]) return 1;
    }
	return 0;
}
void solve(){
	cnt = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	while(check()){
		for(int i = 0; i < n; i++){
			a[(i + 1) % n] = max_(0, a[(i + 1) % n] - a[i]);
		}
	}
	for(int i = 0; i < n; i++){
		if(a[i] && a[(i + 1) % n]) a[(i + 1) % n] = max_(0, a[(i + 1) % n] - a[i]);
		else break;
    }
	for(int i = 0; i < n; i++){
		tmp = (i - 1 + n) % n;
		if((!a[tmp]) && a[i]){
			ans[++cnt] = i + 1;
			tmp2 = (i + 1) % n;
			tmp3 = (i + 2) % n;
			if(a[tmp2] && a[tmp3]){
				tt = a[tmp2] / a[i];
				if(a[tmp3] > (a[tmp2] - a[i] + a[tmp2] - a[i] * tt) * tt / 2){
					ans[++cnt] = tmp3 + 1;
				}
			}
		}
	}
	sort(ans + 1, ans + cnt + 1);
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++) printf("%d ", ans[i]);
	printf("\n");
	return ;
}
int main(){
	scanf("%d", &t);
	for(int kk = 1; kk <= t; kk++){
		solve();
	}
	return 0;
}
```

---

## 作者：jianhe (赞：4)

**upd**：修了一下 latex。

$n$ 只怪物比较多，不好处理，那我们就从小一点的情况入手。

考虑连续 $4$ 只怪物，血量分别为 $0,x,y,z$。则第 $2$ 只永远存活，第 $3$ 只必死。那么我们来考虑第 $4$ 只的死活。

第 $3$ 只对第 $4$ 只发起攻击的次数为 $\lfloor\frac{y}{x}\rfloor$（即第 $2$ 只杀死第 $3$ 只所用次数 $-1$），每次攻击的血量分别为 $y-x,y-2 \times x ,\cdots,y- \lfloor\frac{y}{x}\rfloor \times x$，容易发现这是一个公差为 $x$ 的等差数列，则攻击的血量为 $\frac{(y-x+y-\lfloor\frac{y}{x}\rfloor \times x) \times \lfloor\frac{y}{x}\rfloor}{2}$。这样就可以判断第 $4$ 只的生死了。

再考虑 $n$ 比较大的情况，我们可以先进行若干次暴力操作，手动判断是否有连续的 $4$ 只怪物。如果有，之后就可以进行上述操作了。

下面证明一下时间复杂度：

设进行了 $x$ 操作。则第 $2$ 只血量至少减少了 $x$，第 $3$ 只血量至少减少了 $x^2$，第 $4$ 只血量至少减少了 $x^3$。所以在 $\sqrt[3]{ \max{a_i}}$ 次操作内可以完成。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll T,n,a[N];
int pre(int x){return !x?n-1:x-1;}// 模意义下的前一位 
int nxt(int x){return x+1==n?0:x+1;}// 模意义下的后一位 
bool check(){
	a[n]=a[0],a[n+1]=a[1],a[n+2]=a[2];
	for(int i=0;i<n;i++)// i i+1 i+2 i+3
		if(a[i]&&a[i+1]&&a[i+2]&&a[i+3]) return 1;
	return 0;
}
ll calc(ll s,ll e,ll n){return (s+e)*n/2;}// 等差数列求和  s:首项  e:末项  n:项数 
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;vector<int> ans;
		for(int i=0;i<n;i++) cin>>a[i];
		while(check())// 至少 4 个连续的，存活的 
			for(int i=0;i<n;i++) a[nxt(i)]=max(0ll,a[nxt(i)]-a[i]);// 攻击
		for(int i=0;i<n;i++)// 手动做一遍 
			if(a[i]&&a[nxt(i)]) a[nxt(i)]=max(0ll,a[nxt(i)]-a[i]);
			else break;
		for(int i=0;i<n;i++){
			int i1=pre(i),i2=i,i3=nxt(i),i4=nxt(i3);// i-1 i i+1 i+2 
			if(!a[i1]&&a[i2]){
				ans.push_back(i2+1);
				if(a[i3]&&a[i4]&&a[i4]>calc(a[i3]-a[i2],a[i3]-a[i2]*(a[i3]/a[i2]),a[i3]/a[i2])) ans.push_back(i4+1);
			}
		}
		sort(ans.begin(),ans.end());// 从小到大输出 
		cout<<ans.size()<<"\n";
		for(auto t:ans) cout<<t<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

赛场上写了一个乱搞——`Time limit exceeded on test 55`。乱搞水平不够格。

我们用怪物的血量代指这只怪物。如果有连续的三只怪物 $0$、$x$ 和 $y$（$x \neq 0$），那么在 $y$ 似之前，$x$ 会对他不断产生攻击，那么 $y$ 必定似。

如果有连续的四只怪物 $0$、$x$、$y$、$z$，（$x$、$y \neq 0$），那么我们可以计算 $y$ 对 $z$ 的总伤害。

但是如果有五只以上的连续怪物，问题就变得相当复杂。（我写的乱搞就是处理这一方面的，但是被一个数据爆了 /kel）

考虑现在有四只可爱的小动物 $x$、$y$、$z$、$w$ 排成线，那么最多多少轮会有一个似掉？

假设 $t$ 轮还没人似，那么 $y$ 会收到 $O(t)$ 的伤害，$z$ 会收到 $O(t^2)$ 的伤害，$z$ 会收到 $O(t^3)$ 的伤害。因此在 $O(\sqrt[3] V)$ 的时间内，至少会有一个怪物似掉。（在数学上理解非常直观）

我们暴力跑 $O(\sqrt[3] V)$ 轮，这样就没有长度为 $4$ 以上的怪物连续段，可以套用上述算法。复杂度 $O(n\sqrt[3] V)$。

细节太多，吐了。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,a[MAXN],len[MAXN],b[MAXN];
int pre(int id) {return (id==1)?n:id-1;}
int nxt(int id) {return (id==n)?1:id+1;}
void solve(int u) {
	if(b[nxt(u)]==0||b[nxt(nxt(u))]==0) return ;
	if(b[nxt(nxt(nxt(u)))]==0) return a[nxt(nxt(u))]=0,void();
	long long sum=1ll*(b[nxt(nxt(u))]%b[nxt(u)]+b[nxt(nxt(u))]-b[nxt(u)])*(b[nxt(nxt(u))]/b[nxt(u)])/2;
	if(sum>=b[nxt(nxt(nxt(u)))]) a[nxt(nxt(nxt(u)))]=0;
	return a[nxt(nxt(u))]=0,void();
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i];
		ffor(i,1,n) if(a[i]) len[i]=len[pre(i)]+1; else len[i]=0;
		ffor(i,1,n) if(a[i]) len[i]=len[pre(i)]+1; else len[i]=0;
		if(n<=3) {
			while(1) {
				ffor(i,1,n) a[nxt(i)]=max(0,a[nxt(i)]-a[i]);
				int cnt=0;
				ffor(i,1,n) cnt+=!!a[i];
				if(cnt<=n-1) break ;
			}
			ffor(i,1,n) b[i]=a[i];
			ffor(i,1,n) if(b[i]==0) solve(i);
			vector<int> ans;
			ffor(i,1,n) if(a[i]) ans.push_back(i);
			cout<<ans.size()<<'\n';for(auto id:ans) cout<<id<<' ';cout<<'\n';
			continue ;
		}
		int cnt=0;
		ffor(i,1,n) if(len[i]>=4) cnt++;
		int tpos=1;
		while(cnt) {
			a[nxt(tpos)]=max(0,a[nxt(tpos)]-a[tpos]);
			int olen=len[nxt(tpos)];	
			if(a[nxt(tpos)]) len[nxt(tpos)]=len[tpos]+1;
			else len[nxt(tpos)]=0;
			if(olen>=4&&len[nxt(tpos)]<=3) cnt--;
			tpos=nxt(tpos);
		}
		ffor(i,tpos,n) a[nxt(i)]=max(0,a[nxt(i)]-a[i]);
		tpos=1;
		while(1) {
			if(a[tpos]==0) break ;
			a[nxt(tpos)]=max(0,a[nxt(tpos)]-a[tpos]);
			tpos=nxt(tpos);	
		}
		ffor(i,1,n) b[i]=a[i];
		ffor(i,1,n) if(b[i]==0) solve(i);
		vector<int> ans;
		ffor(i,1,n) if(a[i]) ans.push_back(i);
		cout<<ans.size()<<'\n';for(auto id:ans) cout<<id<<' ';cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Otue (赞：0)

如果连续四只怪物的血量为 $x,y,z,w$ ，并且它们在 $t$ 回合后没有死亡，那么 $y$ 将受到至少 $t$ 点伤害， $z$ 将受到至少 $(t-1) +(t-2)+\cdots=O(t^2)$ 点伤害， $w$ 将受到至少 $O(t^3)$ 点伤害。

设 $V=\max_{i=1}^n a_i$。在 $O(\sqrt[3]{V})$ 个回合后， $x,y,z,w$ 中至少会有一个怪死亡。

$1\leq a_i\leq 10^9$，则最多 $3000$ 个回合后，剩下 $a_i$ 中不为 $0$ 的数组成的连通块大小最多为 $3$。最多为 3 的连通块就可以直接数学方式求解，因为这个连通块是独立的。

坑点注意：处理的连通块的时候要连通首尾。比如：$x,y,0,\dots,z$ 这个数列，若最开始只处理 $x,y$ 连通块，$y$ 就会变成 $0$。但实际操作中，$z$ 可能会将 $x$ 变为 $0$，然后 $y$ 如果特别大则 $x$ 根本无法将 $y$ 变为 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define _for(i, a, b) for (int i = (a); i <= (b); i++) 
const int N = 2e5 + 5;
int n, a[N], b[N], c[N];
vector<int> ans, ans1; 

int get(int x) {
	if (x + 1 <= n) return x + 1;
	if (x == n) return 1;
}

signed main() {
	int T = 0;
	cin >> T;
	while (T--) {
		ans.clear();
		cin >> n;
		int maxn = 0;
		_for(i, 1, n) cin >> a[i], c[i] = a[i], maxn = max(maxn, a[i]);
		int t = cbrt(maxn) * 2 + 20;
		_for(j, 1, t) {
			_for(i, 2, n) a[i] = max(0ll, a[i] - a[i - 1]);
			a[1] = max(a[1] - a[n], 0ll);
		}
		int id = 0;
		_for(i, 1, n) {
			if (!a[i]) {
				id = i;
				break;
			}
		}
		_for(i, 2, id) a[i] = max(0ll, a[i] - a[i - 1]); // 为了避免上述情况，先将开头手动处理
		int i = id;
		_for(w, 1, 2 * n) {
			int x = get(i), y = get(x);
			if (!a[i]) {
				i = get(i);
				continue;
			}
			if (a[x]) {
				a[y] = max(0ll, a[y] - (a[x] / a[i]) * a[x] + a[i] * (1 + a[x] / a[i]) * (a[x] / a[i]) / 2);
				a[x] = 0;
			}
			i = get(i);
		}
		_for(i, 1, n) if (a[i]) ans.push_back(i);
		cout << ans.size() << endl;
		for (auto v : ans) cout << v << ' ';
		puts("");
	}
}
```

---

