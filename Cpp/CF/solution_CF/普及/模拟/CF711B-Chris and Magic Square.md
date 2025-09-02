# Chris and Magic Square

## 题目描述

ZS the Coder and Chris the Baboon arrived at the entrance of Udayland. There is a $ n×n $ magic grid on the entrance which is filled with integers. Chris noticed that exactly one of the cells in the grid is empty, and to enter Udayland, they need to fill a positive integer into the empty cell.

Chris tried filling in random numbers but it didn't work. ZS the Coder realizes that they need to fill in a positive integer such that the numbers in the grid form a magic square. This means that he has to fill in a positive integer so that the sum of the numbers in each row of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/e9e8af3f495bde6f05bb15fe8a019d478bbc6918.png)), each column of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/715dbd8d1021ddf349931cbf725fd485f986bf2d.png)), and the two long diagonals of the grid (the main diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/141aae991a978e02f2d5b71795da24f641569581.png) and the secondary diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/0aa6adfaeb4cdadf568645c01154f2786989c40b.png)) are equal.

Chris doesn't know what number to fill in. Can you help Chris find the correct positive integer to fill in or determine that it is impossible?

## 说明/提示

In the first sample case, we can fill in $ 9 $ into the empty cell to make the resulting grid a magic square. Indeed,

The sum of numbers in each row is:

 $ 4+9+2=3+5+7=8+1+6=15 $ .

The sum of numbers in each column is:

 $ 4+3+8=9+5+1=2+7+6=15 $ .

The sum of numbers in the two diagonals is:

 $ 4+5+6=2+5+8=15 $ .

In the third sample case, it is impossible to fill a number in the empty square such that the resulting grid is a magic square.

## 样例 #1

### 输入

```
3
4 0 2
3 5 7
8 1 6
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 2 1
1 1 1 1
```

### 输出

```
-1
```

# 题解

## 作者：zhang_kevin (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF711B)

[更好的阅读体验？](https://www.luogu.com.cn/blog/zyc-Kevin-Luogu-blog/Solution-CF711B)
# 题意简述

给出一个 $n \times n$ 的矩阵，有一个位置为 `0` ，请你填一个正整数使得这个矩阵成为幻方。

若无法达成输出 `-1` 。

# 解题思路

先输入数据，同时计算出每行的和。

然后，判断是否可以达成幻方。具体方法：找出有几种不同的幻和，大于 $2$ 种直接输出 `-1` 。

若可以达成，则输出**其他行**与**空白点关联的行**的差值。

最后，注意开 `long long`。

# AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[501][501], sum1[501], sum2[501], n, zero, x;
void Put_in(int ans){//把 ans 放进去 
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(!a[i][j]){
				a[i][j] = ans;
				return; 
			}
		}
	}
	return;
}
bool check(int ans){
	int aa, bb, cc;
	Put_in(ans);
	int __sum1 = 0, __sum2 = 0;
	for(int i = 1; i <= n; i++){
		__sum1 += a[i][i];
		__sum2 += a[i][n-i+1];
	}
	//cout << __sum1 << " " << __sum2 << endl;
	if(__sum1 != __sum2){
		return false;
	}
	aa = __sum1;
	int sum[501];
	memset(sum, 0, sizeof(sum));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			sum[i] += a[j][i];
		} 
	}
	int cnt = 0;
	for(int i = 2; i <= n; i++) {
		if(sum[i] != sum[i-1]){
			cnt++;
		}
	}
	//for(int i = 1; i <= n; i++) {
	//	cout << sum[i] << " "; 
	//}
	//cout << endl;
	if(cnt){
		return false;
	}
	bb = sum[1];
	memset(sum, 0, sizeof(sum));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			sum[i] += a[i][j];
		} 
	}
	cnt = 0;
	for(int i = 2; i <= n; i++) {
		if(sum[i] != sum[i-1]){
			cnt++;
		}
	}
	//for(int i = 1; i <= n; i++) {
	//	cout << sum[i] << " "; 
	//}
	//cout << endl;
	if(cnt){
		return false;
	}
	cc = sum[1];
	//cout << aa << " " << bb << " " << cc << " " << endl;
	if(aa != bb || bb != cc || cc != aa){
		return false;
	}
	return true;
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> a[i][j];
			if(!a[i][j]){
				zero = i;
			}
		}
	}
	if(n == 1){//特判 n = 1 
		cout << "1" << endl;
		return 0;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			sum1[i] += a[i][j];
			sum2[i] += a[j][i];
		}
	}
	int cnt1 = 0, cnt2 = 0;
	for(int i = 2; i <= n; i++) {
		if(sum1[i] != sum1[i-1]){
			cnt1++;
		}
		if(sum2[i] != sum2[i-1]){
			cnt2++;
		}
	}
	if(cnt1 > 2 || cnt2 > 2){//如果幻和数量大于 2 
		cout << "-1" << endl;//则无解，输出 -1 
		return 0;//然后结束程序 
	}
	//有解的话
	int other;
	if(zero == 1){
		other = sum1[2];
	}else{
		other = sum1[1];
	}
	int ans = other - sum1[zero];
	if(ans < 1 || !check(ans)){
		ans = -1;
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：___define___ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF711B)

## 思路

我们可以先判断除含 $0$ 以外的列、行、斜边的和是否相等，再判断能否填入一个正整数使其成为一个幻方。这道题就可以解出来了。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define cr {cout<<-1;return 0;}
using namespace std;
int n,a[505][505];
int h[505],z[505],x,x1,q,t;
int l,l1;
bool m1=0,m2=0;
map<int,int> y;
signed main(){
	cin>>n;
	if(n==1) cr
	for(int i=1;i<=n;i++)
	{
		bool s=0;
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]==0) s=1,l1=j;
			h[i]+=a[i][j],z[j]+=a[i][j];
		}
		if(s) q=h[i],l=i;
		else t=h[i],y[h[i]]++;//数组计数 
		if(!s&&h[i]!=h[i-1]&&i!=1&&i-1!=l) cr
		//如果这排不含0，且与上一个不含0的和不等，就可以断定它不是个幻方 
		x+=a[i][i],x1+=a[i][n-i+1];
		if(a[i][i]==0) m1=1;
		if(a[i][n-i+1]==0) m2=1;
	}
	for(int i=2;i<=n;i++)
	{
		if(z[i]!=z[i-1]&&l1!=i&&l1!=i-1) cr
		//如果这列不含0，且与上一个不含0列的和不等 
		if(l1!=i) y[z[i]]++;//数组计数 
	}
	if(l1!=1) y[t]++;
	//如果含0的那一列不为第一列，那第一列就会被漏掉，所以这里要特判 
	if(y[t]!=n*2-2) cr//如果相等的列、排的总数不等于n*2-2（-2代表含零的列与排） 
	if(z[l1]+(t-q)!=h[l]+(t-q)) cr//如果填了之后排与列的和不相等 
	if(m2) if(x1+(t-q)!=t) cr
	if(m1) if(x+(t-q)!=t) cr
	//如果填了之后排与斜边的和不相等 
	if(!m2) if(x1!=t) cr
	if(!m1) if(x!=t) cr
	//判断斜边与排相不相等 
	if(t-q>0) cout<<t-q;
	else cout<<-1;
	//如果要填的这个数为负数 
	return 0;
}
```

要开 `long long`！！！

---

## 作者：CarrotMeow (赞：1)

> 给定一个 $n \times n$ 的矩阵，其中存在且仅存在一个元素 $x$ 为 $0$。判断是否存在 $1 \leq x \leq 10^{18}$，使得填入 $x$ 后矩阵成为幻方。若不存在，输出 $-1$，否则输出找到的 $x$。
>
> 若一个矩阵为幻方，其所有行、列及对角线的和相等。

细节模拟。令空格处于行 $x$ 列 $y$ 的位置。

首先，当 $n = 1$，此时 $x = y = 1$，随便填入一个值即可。

否则建立两个集合 $\{S\}, \{T\}$。可以分为四种情况：

- 行：若当前行 $\neq x$，则将整行的和加入 $S$。否则，加入 $T$。

- 列：若当前列 $\neq y$，则将整列的和加入 $S$。否则，加入 $T$。

- 对角线（左上至右下）：若 $x \neq y$，说明空格不在此条对角线上，则将对角线的和加入 $S$。否则，加入 $T$。

- 对角线（右上至左下）：若 $n - x + 1 \neq y$，说明空格不在此条对角线上，则将对角线的和加入 $S$。否则，加入 $T$。

统计完所有情况后，若 $S$ 或 $T$ 中有 $> 1$ 种值，说明已有行、列或对角线的和不同或者包含空格的若干行、列或对角线的和不同，显然无解。

接下来，先得出不包含空格的一行的和以及包含空格的行 $x$ 的和，两者之差记为 $\mathit{res}$。如果 $res \leq 1$，与题意矛盾，同样无解，否则输出 $\mathit{res}$。

[一些可能的坑点](https://www.luogu.com.cn/discuss/876521)。[代码](https://codeforces.com/contest/711/submission/273966788)。

---

## 作者：yehongxin (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF711B)
## [原题传送门](https://codeforces.com/problemset/problem/711/B)
### 题目大意
给出一个 $n$ 行 $n$ 列的数，有一个数的位置是 $0$，在0的位置处填入一个正整数，是它变成幻方。
### 解题思路
先求出幻和，求出 $0$ 所在的行和，再求出 $0$ 所在的列和，用幻和减去行和和列和，如果相等就输出。如果不相等就输出 $-1$。因此可得出以下代码。
```cpp
if(sum-xsum==sum-ysum)//sum为幻和，xsum与ysum分别为行和和列和
{
	cout<<sum-xsum<<endl;
	return 0;
}
cout<<-1;
```
### 以下为完整参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[505][505],n,sum,xsum,ysum,x,y;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	if(n==1&&a[1][1]==0)
	{
		cout<<1;
		return 0;
	}//如果只有一个数，且为0，就输出1。
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(a[i][j]==0)
			{
				x=i;
				y=j;
				break;
			}
	}//求0所在的位置。
	for(int i=x+1;i<=x+1;i++)
	{
		for(int j=1;j<=n;j++)sum+=a[i][j];
	}//求幻和。
	for(int i=x;i<=x;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]!=0)
			{
				xsum+=a[i][j];
			}
		}
	}//求行和。
	for(int i=1;i<=n;i++)
	{
		for(int j=y;j<=y;j++)
		{
			if(a[i][j]!=0)
			{
				ysum+=a[i][j];
			}
		}
	}//求列和。
	if(sum-xsum==sum-ysum)
	{
		cout<<sum-xsum<<endl;
		return 0;
	}//sum为幻和，xsum与ysum分别为行和和列和。
	cout<<-1;//无解，输出-1。
	return 0;
}
```

---

## 作者：wenxuliang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF711B)

此题主要理解何为幻方。

幻方为任意行列和相等的矩形，因此我们只需计算不涉及到所求数的行列的和即可，以此推出该缺失的行的该数值。


特别的，若以上条件中每个完整行存在和不等时，幻方无解。


****代码：****

```cpp
#include<bits/stdc++.h>
using namespace std;
long long i,j,n,a[1005][1005],s,w;
bool bj,aj;
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)cin>>a[i][j];
	}
  if(n==1&&a[1][1]==0){
    cout<<1;
    return 0;
  }
	for(i=1;i<=n;i++){
		w=0;
		bj=false;
		for(j=1;j<=n;j++){
			if(a[i][j]==0){
				bj=true;
				break;
			}
			else{
				w+=a[i][j];
			}
		}
		if(!bj){
			if(w==s){
			}
			else{
				if(s==0)s=w;
				else{
					cout<<-1;
					aj=false;
					return 0;
				}
			}
		}
	}
	if(!aj)for(i=1;i<=n;i++){
		bj=false;
		w=0;
		for(j=1;j<=n;j++){
			w+=a[i][j];
			if(a[i][j]==0)bj=!bj;
		}
		if(bj){
			cout<<s-w;
			break;
		}
	}
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF711B)

## 题意简述

有一个 $n\times n$ 的未完成的幻方，里面有一个 $0$。要求在 $0$ 的位置填入一个**正**整数，使得这个幻方的每行、每列、两条对角线上的数之和相等。

## 思路

看到 $1 \le n \le 500$，第一反应暴力枚举。我们直接求出每行、每列、两条对角线上的数的和，然后就是分类讨论。

如果已经填好了的行、列、对角线上的和不对，那么由于怎么填都影响不到这些地方，肯定无解。如果未填好的行、列、对角线的和之间不同，那么也是无解。如果需要填进的数是非正数，也无解。更多细节看代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, a[500][500], sr[500], sc[500], sd[2], s, x, y;//注意数据范围 

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	if(n == 1){
		cout << 114514 << endl;//注意特判，填入什么数都可以
		return 0;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> a[i][j];
			sr[i] += a[i][j];//行 
			sc[j] += a[i][j];//列 
			if(i == j){//对角线 
				sd[0] += a[i][j];
			}
			if(i + j == n - 1){
				sd[1] += a[i][j];
			}
			if(a[i][j] == 0){//记录位置 
				x = i;
				y = j;
			}
		}
	}
	if(x == 0){//计算目标和 
		s = sr[1];
	}
	else{
		s = sr[0];
	}
	for(int i = 0; i < n; i++){
		if(i != x){
			if(sr[i] != s){
				cout << -1 << endl;//行的和不对且这行里没有0，无解 
				return 0;
			}
		}
		if(i != y){
			if(sc[i] != s){
				cout << -1 << endl;//列的和不对且这列里没有0，无解 
				return 0;
			}
		}
	}
	if(x != y){//对角线的和不对且这对角线里没有0，无解 
		if(sd[0] != s){
			cout << -1 << endl;
			return 0;
		}
	}
	if(x + y != n - 1){//对角线的和不对且这对角线里没有0，无解 
		if(sd[1] != s){
			cout << -1 << endl;
			return 0;
		}
	}
	if(sr[x] != sc[y]){//无法同时满足行和列，无解 
		cout << -1;
		return 0;
	}
	if(x == y && sd[0] != sr[x]){//无法同时满足行和对角线，无解 
		cout << -1;
		return 0;
	}
	if(x + y == n - 1 && sd[1] != sr[x]){//无法同时满足行和对角线，无解 
		cout << -1;
		return 0;
	}
	if(sr[x] >= s){//注意！答案必须是正整数，这点翻译没有说 
		cout << -1;
		return 0;
	}
	cout << s - sr[x] << endl;
	return 0;
}

```


---

## 作者：kinglf (赞：0)

## [题意回顾](https://www.luogu.com.cn/problem/CF711B)
### 前情提要：

幻方：每一行的和、每一列的和、两条对角线上的和都相等的正方形矩阵，其和称为幻和
### 思路点拨：

根据幻方的特点，我们可以考虑从已知推未知。

#### 已知：

- 不含 0 的行的和=幻和

- 含 0 的行的和+ 0 应表示的数=幻和


所以，可以用不含 0 的行的和（即幻和）减去含 0 的行的和，便可得出 0 应表示的数。最后，将 0 应表示的数代入，判断是否为合法幻方即可。

#### 代码 code :
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,y,a,t,h[505],l[505],xie[5];
int main(){
	scanf ("%lld",&n);
	if (n==1){//特判，只有一个数，填什么都行
		printf ("%lld",1234);
		return 0;
	}
	for (ll i=1;i<=n;i++)
		for (ll j=1;j<=n;j++){
			scanf ("%lld",&a);
			h[i]+=a;//计算每一行的和
			l[j]+=a;//计算每一列的和
			if (i==j)//判断是否在对角线上	
				xie[1]+=a;
			if (i+j==n+1)
				xie[2]+=a;
			if (a==0)
				x=i,y=j;//记录其坐标
		}
	if (x==n) t=h[x-1]-h[x];
	else t=h[x+1]-h[x];//选择不含0的那一行
	if (t<=0){
		puts("-1");
		return 0;//题目要求为正整数
	}			
	h[x]+=t;
	l[y]+=t;//代入
	if (x==y)
		xie[1]+=t;
	if (x+y==n+1)
		xie[2]+=t;
	for (ll i=2;i<=n;i++){
		if (h[i]!=h[i-1]){//不符合幻方的特点就输出-1
			puts("-1");
			return 0;
		}
		if (l[i]!=l[i-1]){//不符合幻方的特点就输出-1
			puts("-1");
			return 0;
		}
	} 
	if (h[n]!=l[n]){//不符合幻方的特点就输出-1
		puts("-1");
		return 0;
		
	}
	if (xie[1]==xie[2]&&xie[2]==h[n])//不符合幻方的特点就输出-1
		printf ("%lld",t);
	else printf ("-1");
	

	return 0;
}
```


---

## 作者：YCS_GG (赞：0)

### CF711B Chris and Magic Square

#### 题意

给出一个$n\times n$的矩阵，有一个位置缺少一个数字，请你填一个正整数使得这个矩阵每行每列与两条对角线之和相等

若无法达成则输出$-1$

#### Solution

还是很水的，记录每行每列对角线的值，如果超过三个一定无解

若有解则与空白点关联的行列对角线一定和相同，这时候填入一个其他行与这一行的差值即可

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll a[1001][1001];
ll r[1001];
ll c[1001];
int n;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int x, y;
    ll pdsum = 0;
    ll sdsum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 0) {
                x = i;
                y = j;
            } else {
                r[i] += a[i][j];
                c[j] += a[i][j];
                if (i == j) {
                    pdsum += a[i][j];
                }
                if (i + j == n - 1) {
                    sdsum += a[i][j];
                }
            }
        }
    }
    if (n == 1) {
        cout << 233 << '\n';
        return 0;
    }
    ll commonsum = r[0];
    if (x == 0) {
        commonsum = r[1];
    }
    ll rowsum = -1;
    ll colsum = -1;
    ll d1sum  = -1;
    ll d2sum  = -1;
    for (int i = 0; i < n; i++) {
        if (i != x) {
            if (r[i] != commonsum) {
                cout << -1 << endl;
                return 0;
            }
        } else {
            rowsum = r[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != y) {
            if (c[i] != commonsum) {
                cout << -1 << endl;
                return 0;
            }
        } else {
            colsum = c[i];
        }
    }
    bool isd1 = false;
    bool isd2 = false;
    if (x == y)
        isd1 = true;
    if (x + y == n - 1)
        isd2 = true;
    if (!isd1) {
        if (pdsum != commonsum) {
            cout << -1 << endl;
            return 0;
        }
    } else {
        d1sum = pdsum;
    }
    if (!isd2) {
        if (sdsum != commonsum) {
            cout << -1 << endl;
            return 0;
        }
    } else {
        d2sum = sdsum;
    }
    if (rowsum == colsum) {
        if (isd1 && d1sum != rowsum) {
            cout << -1 << endl;
            return 0;
        }
        if (isd2 && d2sum != rowsum) {
            cout << -1 << endl;
            return 0;
        }
        ll value = commonsum - rowsum;
        if (value > 0) {
            cout << value << '\n';
            return 0;
        } else {
            cout << -1 << endl;
            return 0;
        }
    } else {
        cout << -1 << endl;
        return 0;
    }
}
```



---

