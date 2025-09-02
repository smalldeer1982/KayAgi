# Feeding Chicken

## 题目描述

Long is a huge fan of CFC (Codeforces Fried Chicken). But the price of CFC is increasing, so he decides to breed the chicken on his own farm.

His farm is presented by a rectangle grid with $ r $ rows and $ c $ columns. Some of these cells contain rice, others are empty. $ k $ chickens are living on his farm. The number of chickens is not greater than the number of cells with rice on the farm.

Long wants to give his chicken playgrounds by assigning these farm cells to his chickens. He would like to satisfy the following requirements:

- Each cell of the farm is assigned to exactly one chicken.
- Each chicken is assigned at least one cell.
- The set of cells assigned to every chicken forms a connected area. More precisely, if two cells $ (x, y) $ and $ (u, v) $ are assigned to the same chicken, this chicken is able to walk from $ (x, y) $ to $ (u, v) $ by passing only its cells and moving from each cell to another cell sharing a side.

Long also wants to prevent his chickens from fighting for food. Hence he wants the difference between the maximum and the minimum number of cells with rice assigned to a chicken to be as small as possible. Please help him.

## 说明/提示

These pictures explain the sample output. Each color represents one chicken. Cells filled with patterns (not solid colors) contain rice.

In the first test case, each chicken has one cell with rice. Hence, the difference between the maximum and the minimum number of cells with rice assigned to a chicken is $ 0 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/1bff8ca11bd265337b0e871e2919557b9f31df1c.png)

In the second test case, there are $ 4 $ chickens with $ 3 $ cells of rice, and $ 2 $ chickens with $ 2 $ cells of rice. Hence, the difference between the maximum and the minimum number of cells with rice assigned to a chicken is $ 3 - 2 = 1 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/2ec7f9b3f1d8e0f97ddc9a49d6dcde16eae965cb.png)

In the third test case, each chicken has $ 3 $ cells with rice. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/cc5ea14ecb6cc9df893cd1ba4b47e078c09da70f.png)

In the last test case, since there are $ 62 $ chicken with exactly $ 62 $ cells of rice, each chicken must be assigned to exactly one cell. The sample output is one of the possible way.

## 样例 #1

### 输入

```
4
3 5 3
..R..
...R.
....R
6 4 6
R..R
R..R
RRRR
RRRR
R..R
R..R
5 5 4
RRR..
R.R..
RRR..
R..R.
R...R
2 31 62
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
```

### 输出

```
11122
22223
33333
aacc
aBBc
aBBc
CbbA
CbbA
CCAA
11114
22244
32444
33344
33334
abcdefghijklmnopqrstuvwxyzABCDE
FGHIJKLMNOPQRSTUVWXYZ0123456789```

# 题解

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1254A)

首先我们要知道每只鸡需要多少米。为了使米数的极差最小，肯定要让每只鸡平均分米的格子。那么可能有些鸡需要多一格米。知道了每只鸡需要的米数后就可以开始构造了。

我们把整个养鸡场按照蛇形变成一条链，如图（其中 `R` 表示有米的格子）：

![](https://cdn.luogu.com.cn/upload/image_hosting/q1petd6f.png)

假设在图示样例中有 $5$ 只鸡，那么其中 $1$ 只鸡分到 $2$ 格米，$4$ 只鸡分到 $1$ 格米。

那么我们从蛇形的起点开始遍历，对于每只鸡，当遇到足够的米时就停止，换另一只鸡。这样可以保证每只鸡的地盘都是沿着蛇形联通的。假设我们让第一只鸡获得 $2$ 格米，那么它的地盘应该长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/q9hcewha.png)

图中的情况进行完遍历后如图，都是按照蛇形分布的：

![](https://cdn.luogu.com.cn/upload/image_hosting/eipt7chm.png)

最后别忘了剩下的空缺要由最后一只鸡补上。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
int t, r, c, k, cnt, x, y, cnt2;
char a[201][201], ans[201][201];
pii nex(int x, int y){//用于确定下一个遍历的位置
	if (y == c && x % 2 == 1) x++;
	else if (y == 1 && x % 2 == 0) x++;
	else if (x % 2 == 1) y++;
	else y--;
	pii p; p.first = x, p.second = y; return p;
}
char get(int x){//获得对应的字符
	if (x <= 10) return x + '0' - 1;
	if (x <= 36) return x + 'A' - 11;
	return x + 'a' - 37;
}
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d%d%d", &r, &c, &k); cnt = 0;
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++){cin >> a[i][j]; if (a[i][j] == 'R') cnt++;}
		int n = cnt / k, m = cnt % k; x = 1, y = 1;
		for (int i = 1; i <= m; i++){//比正常的鸡多一格米
			cnt2 = 0;
			while (cnt2 < n + 1){
				ans[x][y] = get(i);
				if (a[x][y] == 'R') cnt2++;
				pii p = nex(x, y); x = p.first, y = p.second;
			}
		}
		for (int i = m + 1; i <= k; i++){//正常的鸡
			cnt2 = 0;
			while (cnt2 < n){
				ans[x][y] = get(i);
				if (a[x][y] == 'R') cnt2++;
				pii p = nex(x, y); x = p.first, y = p.second;
			}
		}
		while (x != r + 1){//补上空缺
			ans[x][y] = get(k);
			pii p = nex(x, y); x = p.first, y = p.second;
		}
		for (int i = 1; i <= r; i++){
			for (int j = 1; j <= c; j++) cout << ans[i][j];
			puts("");
		}
	}
    return 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：0)

我们先遍历一遍矩阵，求出 $R$ 的总个数，我们令其为 $sum$。

每个连通块中应该包含 $\lfloor \frac{sum}{k} \rfloor$ 个 $R$（$k$ 的定义为题面里的定义），特别的，有 $sum \bmod k$ 个连通块中有 $\lfloor\frac{sum}{k}\rfloor+1$ 个 $R$。

我们再蛇形遍历矩阵，填上划分方案即可。

什么是蛇形遍历矩阵？举个例子，以下是蛇形遍历一个 $3\times3$ 的矩阵，其中数字表示这个点是第几个被遍历的。

```
123
654
789
```

最后代码如下：

```cpp
char _ans_[70];
int n,m,k,s[70];
char f[105][105];
void init(){
	for(int i=1;i<=10;i++) _ans_[i]='0'+i-1;
	for(int i=11;i<=36;i++) _ans_[i]='A'+i-11;
	for(int i=37;i<=62;i++) _ans_[i]='a'+i-37;
}//预处理划分方案字符
void solve(){
	int sum=0,cnt=1;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		cin>>f[i][j];
		sum+=(f[i][j]=='R');
	}
	for(int i=1;i<=k;i++){
		s[i]=sum/k;
		if(i<=sum%k) s[i]++;
	}
	for(int i=1;i<=n;i++){
		if(i%2){
			for(int j=1;j<=m;j++){
				if(f[i][j]=='R') s[cnt]--;
				f[i][j]=_ans_[cnt];
				if(!s[cnt]) cnt++;
				if(cnt>k) cnt--;
			}
		}
		else{
			for(int j=m;j;j--){
				if(f[i][j]=='R') s[cnt]--;
				f[i][j]=_ans_[cnt];
				if(!s[cnt]) cnt++;
				if(cnt>k) cnt--;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<f[i][j];
		cout<<"\n";
	}
}
```

---

## 作者：Saber_Master (赞：0)

容易发现，$k\geq1$时，最大差值为$1$.设$R$的个数为$cnt$,则我们可以将其分解为$cnt%k$个含$\lfloor\frac{cnt}{k}\rfloor+1$个$R$的联通块和$k-cnt%k$个含$\lfloor\frac{cnt}{k}\rfloor$个$R$的联通块,然后蛇形扫描即可.这里有一点要注意的是，如果存在$cnt\leq k$,为了能够兼容上面解法，我们可以随便补$k-cnt$个$R$进去，然后扫描.

$O(\sum r\cdot c)$

核心代码

```cpp
inline void solve(){
	read(n); read(m); read(k);
	cnt=0;
	char wn;
	for (R ll i=1; i<=n; i++){
		for (R ll j=1; j<=m; j++){
			wn=getchar();
			while (wn!='.' && wn!='R') wn=getchar();
			c[i][j]=wn;
			if (wn=='R') ++cnt;
		}
	}
	if(cnt<k){
		for (R ll i=1; i<=n && cnt<k; i++)
			for (R ll j=1; j<=n && cnt<k; j++)
				if (c[i][j]=='.')
					++cnt, c[i][j]='R';
	}
	
//	(cnt%k) cnt/k+1
//	(k-cnt%k) cnt/k
	rem=(cnt%k); goal=cnt/k+1;
	ll step=1;
	ll nowl=1, nowr=0;
	ll color=0;
	for (R ll i=1; i<=rem; i++){
		++color;
		ll now=0;
		while (now<goal){
			nowr+=step;
			if (nowr<=0 || nowr>m) ++nowl, step=-step, nowr+=step;
			if (c[nowl][nowr]=='R') ++now;
			col[nowl][nowr]=color;
		}
	}
	rem=k-cnt%k; goal=cnt/k;
	for (R ll i=1; i<=rem; i++){
		++color;
		ll now=0;
		while (now<goal){
			nowr+=step;
			if (nowr<=0 || nowr>m) ++nowl, step=-step, nowr+=step;
			if (c[nowl][nowr]=='R') ++now;
			col[nowl][nowr]=color;
		}
	}
	while (nowl<=n){
		nowr+=step;
		if (nowr<=0 || nowr>m) ++nowl, step=-step, nowr+=step;
		col[nowl][nowr]=color;
	}
	
	for (R ll i=1; i<=n; i++){
		for (R ll j=1; j<=m; j++)
			putchar(res[col[i][j]]); putchar('\n');
	}
}
```


---

## 作者：寒鸽儿 (赞：0)

首先肯定是有合法的划分方案的。  
然后考虑怎么分。  
我们考虑以蛇字形(参见部分考场的座位号分布)来遍历整个图,这样就可以使得走过的路径上被任意断开,中间的部分是连通块。  
然后满足条件就划分好了。具体的,有两种鸡,一种为均值,一种为均值+1,这里只要任何一个条件达到了就应当结束对这只鸡的分配。(不要试图先为一种鸡分配再为另一种分配,这样不一定有合法的划分)  
建议按照枚举遍历的时间戳根据时间戳计算坐标比较好。  
细节有些多。  
```cpp
#include <cstdio>

using namespace std;

const char name[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int N = 123;

inline int read() {
	char ch = getchar();
	while(ch != '.' && ch != 'R') ch = getchar();
	return ch == 'R';
}

int a[N][N];
char res[N][N];

inline void getpt(int r, int c, int id, int &xi, int &yi) {
	xi = (id - 1) / c + 1, yi = xi % 2 ? id - (xi-1) * c : c - (id - (xi-1) * c) + 1;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int sum = 0, r, c, k, xi, yi;
		scanf("%d %d %d", &r, &c, &k);
		for(int i = 1; i <= r; ++i)
			for(int j = 1; j <= c; ++j) {
				a[i][j] = read();
				sum += a[i][j];
			}
		if(!k) {
			for(int i = 1; i <= k; ++i) {
				getpt(r, c, i, xi, yi);
				res[xi][yi] = name[i];
			}
			for(int i = k + 1; i <= r * c; ++i) {
				getpt(r, c, i, xi, yi);
				res[xi][yi] = name[k];
			}
		} else {
			int one = sum / k, ls = sum % k, rs = k - ls;
			int i = 1, pp = 1, tmp = 0;
			for(; i <= r * c; ++i) {
				if(pp > k) break;
				getpt(r, c, i, xi, yi);
				res[xi][yi] = name[pp]; tmp += a[xi][yi];
				if(tmp == one + 1 && ls > 0 || rs > 0 && tmp == one) {
					if(tmp == one) --rs;
					else --ls;
					tmp = 0; ++pp;
				}
			}
			for(; i <= r * c; ++i) {
				getpt(r, c, i, xi, yi);
				res[xi][yi] = name[k];
			}
		}
		for(int i = 1; i <= r; ++i) {
			for(int j = 1; j <= c; ++j) {
				printf("%c", res[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

