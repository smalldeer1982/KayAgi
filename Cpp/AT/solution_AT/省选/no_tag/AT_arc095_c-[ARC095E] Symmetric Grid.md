# [ARC095E] Symmetric Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc095/tasks/arc095_c

$ H $ 行 $ W $ 列のマス目があり，各マスには英小文字が書かれています． 具体的には，上から $ i $ 行，左から $ j $ 列目のマスに書かれている文字は，文字列 $ S_i $ の $ j $ 文字目に等しいです．

すぬけ君は，このマス目に対して次の操作を好きな回数行うことができます：

- $ 2 $ つの異なる行を選び，入れ替える．または，$ 2 $ つの異なる列を選び，入れ替える．

すぬけ君は，このマス目が点対称的になるようにしたいです． すなわち，任意の $ 1\ \leq\ i\ \leq\ H $, $ 1\ \leq\ j\ \leq\ W $ に対して，マス目の上から $ i $ 行，左から $ j $ 列目に書かれている文字と，マス目の上から $ H\ +\ 1\ -\ i $ 行，左から $ W\ +\ 1\ -\ j $ 列目に書かれている文字が等しくなるようにしたいです．

すぬけくんがこの目標を達成することが可能かどうか判定してください．

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 12 $
- $ 1\ \leq\ W\ \leq\ 12 $
- $ |S_i|\ =\ W $
- $ S_i $ は英小文字のみからなる

### Sample Explanation 1

下の画像に示すように，左から $ 2 $ 列目と $ 3 $ 列目を入れ替えると，マス目が点対称的になります． !\[\](https://img.atcoder.jp/arc095/2b61caf45e7c5c7311e3944f3418b0bb.png)

## 样例 #1

### 输入

```
2 3
arc
rac```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 7
atcoder
regular
contest```

### 输出

```
NO```

## 样例 #3

### 输入

```
12 12
bimonigaloaf
faurwlkbleht
dexwimqxzxbb
lxdgyoifcxid
ydxiliocfdgx
nfoabgilamoi
ibxbdqmzxxwe
pqirylfrcrnf
wtehfkllbura
yfrnpflcrirq
wvcclwgiubrk
lkbrwgwuiccv```

### 输出

```
YES```

# 题解

## 作者：Qiaoqia (赞：9)

我们观察一下题面，发现有以下性质：

1. 只有 YES/NO
2. 数据范围只有 $12$。
3. 不多测。

那么一种邪恶的想法就出现了：模拟退火。  

估价函数就用没有匹配上的对数就可以了。

```cpp
// SA yyds!

#include <bits/stdc++.h>
int n, m;
struct twt { char a[20][20]; } t;
int h(twt x) {
	int an = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			an += x.a[i][j] != x.a[n-i+1][m-j+1];
	return an;
}
void SA() {
	std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
	double T = 10000, delta = 0.966;
	while (T > 1e-8) {
		int opt = rnd() % 2;
		twt s = t;
		if (opt) {
			int x = rnd() % n + 1, y = rnd() % n + 1;
			for (int i = 1; i <= m; i++) std::swap(t.a[x][i], t.a[y][i]);
		}
		else {
			int x = rnd() % m + 1, y = rnd() % m + 1;
			for (int i = 1; i <= n; i++) std::swap(t.a[i][x], t.a[i][y]);
		}
		if (h(s) < h(t) || exp(-delta/T) > (double)rnd()/2147483647)
			t = s;
		T *= delta;		
	}
	if (h(t) == 0) std::cout << "YES\n";
	else std::cout << "NO\n";
}
int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			std::cin >> t.a[i][j];
	SA();
}
```

---

## 作者：feecle6418 (赞：8)

发现我不会 深度优先搜索+剪枝 了 /fad

首先肯定希望把行和列的操作独立开来，所以先把行的操作做完再去管列的操作。肯定不能直接枚举怎么做行的操作，但注意到在终状态下，只有**哪些行配对**这个事情影响最终结果（比如我钦定最终状态下初始第一行和初始第四行是对称的，初始第二行和初始第三行是对称的，那最终行的排列是 `1234` 和 `1324` 其实是一样的）。所以只需要枚举匹配方案，最坏情况下是 $(n-1)!!$ 级别的（已经可以接受了），但实际上由于匹配的行字符集合必须相同，所以甚至达不到。

然后再考虑列的操作，由于行的顺序已经确定，所以相当于把相互对称的列两两配对，问能否配完或只剩一列。这里

- 如果 $m$ 奇，枚举哪一列不配对，剩下的列用一个 map 统计即可。
- 否则直接用一个 map 统计。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mch[20],vst[20];
char a[20][20],b[20][20]; 
void Try(bool has){
	memset(vst,0,sizeof(vst));
	int w=1;
	for(int i=1;i<=n;i++){
		if(vst[i]||!mch[i])continue;
		for(int j=1;j<=m;j++)b[w][j]=a[i][j];
		for(int j=1;j<=m;j++)b[n-w+1][j]=a[mch[i]][j];
		w++;
		vst[mch[i]]=vst[i]=1;
	}
	if(has){
		for(int i=1;i<=n;i++)if(!mch[i])for(int j=1;j<=m;j++)b[(n+1)/2][j]=a[i][j];
	}
	if(m&1){
		for(int j=1;j<=m;j++){
			int fl=1;
			for(int i=1;i<=n;i++){
				if(b[i][j]!=b[n-i+1][j])fl=0;
			}
			if(fl){
				map<string,int> mp;
				for(int k=1;k<=m;k++){
					if(k==j)continue;
					string u;
					for(int l=1;l<=n;l++)u+=b[l][k];
					mp[u]++;
				}
				for(auto k:mp){
					auto s=k.first;
					reverse(s.begin(),s.end());
					if(s==k.first){
						if(mp[s]&1)return ;
						continue;
					}
					if(mp[s]!=k.second)return ;
				}
				puts("YES"),exit(0);
			}
		}
	}
	else {
		map<string,int> mp;
		for(int k=1;k<=m;k++){
			string u;
			for(int l=1;l<=n;l++)u+=b[l][k];
			mp[u]++;
		}
		for(auto k:mp){
			auto s=k.first;
			reverse(s.begin(),s.end());
			if(s==k.first){
				if(mp[s]&1)return ;
				continue;
			}
			if(mp[s]!=k.second)return ;
		}
		puts("YES"),exit(0);
	}
}
void dfs(int x,int has){
	if(x==n+1)return Try(has);
	if(mch[x])return dfs(x+1,has);
	for(int i=x+1;i<=n;i++){
		if(mch[i])continue;
		mch[i]=x,mch[x]=i;
		dfs(x+1,has);
		mch[i]=0,mch[x]=0;
	}
	if(!has)dfs(x+1,has+1);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	dfs(1,0);
	puts("NO");
}
```

---

## 作者：野生林登万 (赞：2)

## 遗传算法
首先观察题目范围很小，看上去可以随机化乱搞。相信各位都能想到模拟退火，不过其实还有一个算法竞赛中基本不会用到（事实上咱没有在 OI 题目中见过这个算法）的算法——遗传算法  
不知道各位是否听说过遗传算法，它的核心思想就像生物学里的进化论一样，优胜劣汰。其实学习过生物学的各位听到这个名字应该可以自行推理出它的几个基本步骤：  

  1.变异：随机交换某一行或某一列，模仿生物中的变异过程；  
  2.择优：按照中心对称的失配数（你可以看做一个估价函数）排序；   
  3.适者生存：按照参数将后几名的对象淘汰，用前几名的参数赋值给他们。  
  
然后循环以上几个步骤直到出现中心对称的情况输出 `yes` 或者循环次数达到上限输出 `no` 就行了。  
事实上实际应用中的遗传算法比起这个要复杂得多，你也可以引入更多的随机变量或者多次运行算法防止陷入局部最优解。不过只是解决这道题的话上述这个最基本的模型已经够用了。这段代码非常简洁，咱应该 $10min$ 左右就写完了（~~切紫题最舒服的一次~~）  
另外遗传算法在算法竞赛中的使用其实非常有限，本文权当科普了。一般来说还是要写模拟退火  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 14;
const int SIZE = 10;
const int LIVE = 5;
mt19937 rng(time(0));
int n,m;
struct POP{
	int nowval;
	char c[MAXN][MAXN];
	inline void Shuffle(){
		bool UD = rng() % 2;
		int up = UD ? n : m;
		int l = (rng() % up) + 1,r = (rng() % up) + 1;
		if(UD){
			for(int i = 1;i <= m;i++){
				swap(c[l][i],c[r][i]);
			}
		}else{
			for(int i = 1;i <= n;i++){
				swap(c[i][l],c[i][r]);
			}
		}
		return ;
	}
	inline void Calc(){
		nowval = 0;
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				const int OPi = (n + 1) - i,OPj = (m + 1) - j;
				nowval += c[i][j] != c[OPi][OPj];
			}
		}
		return ;
	}
}pop[SIZE + 2];
bool Cmp(POP p1,POP p2){
	return p1.nowval < p2.nowval;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin>>pop[1].c[i][j];
		}
	}
	for(int i = 2;i <= SIZE;i++){
		pop[i] = pop[1];
	}
	int t = 10000;
	while(t--){
		for(int i = 1;i <= SIZE;i++){
			pop[i].Shuffle();
		}
		for(int i = 1;i <= SIZE;i++){
			pop[i].Calc();
		}
		sort(pop+1,pop+SIZE+1,Cmp);
		if(pop[1].nowval == 0){
			cout<<"YES"<<endl;
			return 0;
		}
		for(int i = LIVE+1;i <= SIZE;i++){
			pop[i] = pop[(i % LIVE)+1];
		}
	}
	cout<<"NO"<<endl;
	return 0;
}
```

---

