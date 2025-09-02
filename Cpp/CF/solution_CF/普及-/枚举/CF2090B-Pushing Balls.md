# Pushing Balls

## 题目描述

Ecrade 有一个 $$$n \times m$$$ 的网格，初始为空。他通过多次（可能为零次）推球操作在其中放置了若干球。

每次操作时，他可以选择从某行的最左边缘或某列的最上边缘向网格内推入一个球。

当一个球朝某个方向移动时：
- 若目标位置原本没有球，则新推入的球会占据该位置并停止。
- 若目标位置已有球，则新推入的球会占据该位置，而原位置的球将继续沿相同方向移动到下一个位置。

注意：若某行或某列已满（即该行或列所有位置都有球），则不能从该行或列推入新球。

给定网格每个位置是否有球的最终状态，请判断是否存在一种推球操作序列使得最终状态可以被达成。

## 说明/提示

为简化描述：
- 若从第 $$$i$$$ 行的最左边缘推入球，称该操作为 $$$\text{ROW}\\ i$$$
- 若从第 $$$i$$$ 列的最上边缘推入球，称该操作为 $$$\text{COL}\\ i$$$

以下示例矩阵中的非零数字 $$$x$$$ 表示第 $$$x$$$ 次推入的球。

第一个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 3}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}0&0&0\\\\0&0&0\\\\2&1&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}0&0&4\\\\0&0&3\\\\2&1&0\end{pmatrix}$$$

第二个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2} \begin{pmatrix}0&0&0\\\\3&2&1\\\\0&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 2}\xrightarrow{\text{COL}\\ 2} \begin{pmatrix}0&5&0\\\\3&4&1\\\\0&2&0\end{pmatrix}$$$

第三个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}1&0&0\\\\2&0&0\\\\3&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}1&0&6\\\\2&0&5\\\\3&0&4\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}7&1&6\\\\8&2&5\\\\9&3&4\end{pmatrix}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 3
001
001
110
3 3
010
111
010
3 3
111
111
111
3 3
000
000
000
3 3
000
000
001```

### 输出

```
YES
YES
YES
YES
NO```

# 题解

## 作者：hongshixiaobai (赞：3)

# CF2090B Pushing Balls 题解
[传送门](https://www.luogu.com.cn/problem/CF2090B)
## 题意
给你一个 $n \times m$ 的矩阵，初始为空，每次操作你可以从上方和左侧推入一些球，给定一个状态，问能否通过若干次操作得到
## 思路
一个位置有球为 $1$，无球为 $0$，显然如果对于每个有球的位置只有其同一列上方所有位置或同一行左侧所有位置都有球才合法，使用二维前缀和维护即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[55][55],pre[55][55],i,j;
bool flag;
char c;
int main()
{
	cin>>t;
	while(t--)
	{
		flag = 0;
		cin>>n>>m;
		for(i = 1;i<=n;i++)
		{
			while(c!='0'&&c!='1')c = getchar();
			for(j = 1;j<=m;j++)
			{
				a[i][j] = c-'0';
				c = getchar();
			}
		}
		for(i = 1;i<=n;i++)
			for(j = 1;j<=m;j++)
				pre[i][j] = pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+a[i][j];
		for(i = 1;i<=n;i++)
		{
			for(j = 1;j<=m;j++)
			{
				if(a[i][j] == 1&&pre[i][j]-pre[i][j-1]!=i&&pre[i][j]-pre[i-1][j]!=j)
				{
					cout<<"NO\n";
					flag = 1;
					break;
				}
			}
			if(flag)break;
		}
		if(flag)continue;
		cout<<"YES\n";
	}
}
```

---

## 作者：shicj (赞：1)

贪心地，依次扫描每一行（列），如果当前格子有球，将它打上标记，如果没有球且之前没有打过标记，直接进入下一行（列），最终统计有没有**有球而没有标记**的格子，如果有，说明不合法，否则合法。

```cpp
#include<bits/stdc++.h>
using namespace std;
string mp[100005];
int n,m;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		string tmp;
		cin>>mp[i];
		mp[i]=" "+mp[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]!='0'){
				mp[i][j]='2';
			}
			else{
				break;
			}
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(mp[i][j]!='0'){
				mp[i][j]='2';
			}
			else{
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='1'){
				cout<<"NO"<<endl;
				return;
			}
		}
	}
	cout<<"YES"<<endl;
}
int main(){
#ifdef USE_FILE_IO
	freopen("code.in","r",stdin);
	cerr<<"[File IO]"<<endl;
#endif
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
给定一个表格，请问这个表格能否使得每个球的左边或者上面全都有球。
## 题目解法
直接按照题意做即可，参考代码如下，复杂度为 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1010;

int t, n, m, flag;
char a[kMaxN][kMaxN];

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; flag = 0) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (a[i][j] == '1') {
          int flag1 = 0, flag2 = 0;
          for (int k = 1; k < j; k++) {
            flag1 |= a[i][k] == '0';  // 判断左边是否都为 1
          }
          for (int k = 1; k < i; k++) {
            flag2 |= a[k][j] == '0';  // 判断上边是否都为 1
          }
          flag |= flag1 && flag2;  // 如果上面和左边都不满足，则这个表格不满足条件
        }
      }
    }
    cout << (flag ? "NO\n" : "YES\n");  // 输出答案
  }
  return 0;
}
```
## 题目解法 Plus
我们如果想让时间变快，那么要让判断的时间变小，所以可以做前缀和，即可 $O(1)$ 判断，复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1010;

int st[2][kMaxN][kMaxN], t, n, m, flag;
char a[kMaxN][kMaxN];

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; flag = 0) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
        st[0][i][j] = st[0][i][j - 1] + (a[i][j] == '1');
        st[1][i][j] = st[1][i - 1][j] + (a[i][j] == '1');  // 做两个前缀和，统计球的数量
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (a[i][j] == '1' && st[0][i][j] < j && st[1][i][j] < i) {  // 判断前面的小球是否都在
          flag = 1;
          break;
        }
      }
    }
    cout << (flag ? "NO\n" : "YES\n");  // 输出即可
  }
  return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2090B](https://www.luogu.com.cn/problem/CF2090B) || [CodeForces 2090 B](https://codeforces.com/contest/2090/problem/B)

### 简要题意
对于一个 $n\times m$ 的网格，进行了若干次操作，每次往网格的最上端或者最左端推入一个球，如果最上端或者最左端已经有球，那么之前的球会向下或向右（即被推至里部）以空出位置给新推入的球。

现给出网格的最终状态，判断其是否合法，即是否可以通过题目所述的方法达到此状态。

### 思路
对于每个有球的格子，球只可能从行首或列首推入，并由其他球推到该位置。因此其上所有的格子或其左所有的格子必有其一是被球填满的，以表明球是从此方向推入而来的。

因此，对于每个球，我们检查每个球上方所有的格子是否都为 $1$，或左边所有的格子是否都为 $1$，满足其一即可。如果二者皆不满足，证明此状态是不合法的。

为降低时间复杂度，可以先预处理出每个球的上方格子或左边格子是否皆为 $1$，并存储在 `r_pre` 与 `c_pre` 中。

[通过记录](https://codeforces.com/contest/2090/submission/311979722)

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        vector<vector<bool>> c_pre(m, vector<bool>(n + 1, false));
        vector<vector<bool>> r_pre(n, vector<bool>(m + 1, false));
        for (int i = 0; i < n; ++i)
        {
            r_pre[i][0] = true;
            for (int j = 1; j <= m; ++j) r_pre[i][j] = r_pre[i][j - 1] && (a[i][j - 1] == '1');
        }
        for (int j = 0; j < m; ++j)
        {
            c_pre[j][0] = true;
            for (int i = 1; i <= n; ++i) c_pre[j][i] = c_pre[j][i - 1] && (a[i - 1][j] == '1');
        }
        bool flag = true;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (a[i][j] == '1')
                {
                    bool R = r_pre[i][j];
                    bool C = c_pre[j][i];
                    if (!R && !C)
                    {
                        flag = false;
                        goto end;
                    }
                }
            }
        }
    end:
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

---

## 作者：__hjyakioi__ (赞：0)

显然，对于一个有球的位置，它必须满足上边或左边全部有球。如果有空位，那么推进来的球会先把空位占了，之后进来的才会占这个位置。\
分别维护行和列的前缀按位与的值即可。\
复杂度 $O(n^2)$。\
[code](https://codeforces.com/contest/2090/submission/311975860)

---

## 作者：yhl110804 (赞：0)

只有当本行或本列的所有一均在某一连续的由一行或一列发端的一中，该矩阵才符合题意。记录每一行和列一的终止位置,若它们剩余部分的交集中有一，则不符题意。
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
//#define eps 1e-9
//#define ENF 1e13
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	return x*f;
}
void write(int x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
const int N=1e2;
const int mod=1e9+7;
int ksm(int a,int b) {
	long long ret=1;
	while(b) {
		if(b&1)(ret*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ret%mod;
}
void T_() {
	int sum=0;
	while(sum<=3e9)sum++;
}
struct node {
	int x,y;
};
int n,m;
int mp[N][N];
int id[N];
int idd[N];
void clear(){
	for(int i=1;i<=n;i++)id[i]=0;
	for(int j=1;j<=m;j++)idd[j]=0;
}
void solve() {
	n=read(),m=read();
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			char ch;
			cin>>ch;
			mp[i][j]=ch-'0';
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;j++){
			if(!mp[i][j]){
				id[i]=j;
				break;
			}
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(!mp[i][j]){
				idd[j]=i;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!id[i])continue;
		for(int j=id[i];j<=m;j++){
			if(mp[i][j]&&idd[j]<i&&idd[j]!=0){
				cout<<"NO\n";
				clear();
				return;
			}
		}
	}
	for(int j=1;j<=m;j++){
		if(!idd[j])continue;
		for(int i=idd[j];i<=n;i++){
			if(mp[i][j]&&id[i]<j&&id[i]!=0){
				cout<<"NO\n";
				clear();
				return;
			}
		}
	}
	cout<<"YES\n";
	clear();
	return;
}
signed main() {
	int T=read();
	while(T--)solve();
	return 0;
}

```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{53}$ 篇题解。

# $\mathbf{0x01}$ 承

在一个网格的上面和左面推球，判断最终状态是否合法。

# $\mathbf{0x02}$ 转

显而易见的，如果一个球能被推到这个位置，就说明它的上面或左面一定有一个方向全是球，依次遍历每一个点，如果这个点有球且向上和向左都不合法，则无解。

时间复杂度 $\Theta(n^3)$。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,m;
char a[55][55];
void solve(){
	cin>>n>>m;
	memset(a,0,sizeof(a));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	map<pair<ll,ll>,bool>mp;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			bool fh=1,fl=1;
			for(ll k=j-1;k>=1;k--){
				if(a[i][k]=='0'){
					fh=0;
					break;
				}
			}
			for(ll k=i-1;k>=1;k--){
				if(a[k][j]=='0'){
					fl=0;
					break;
				}
			}
			mp[{i,j}]=(fh||fl);
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(a[i][j]=='1'&&mp[{i,j}]==0){
				cout<<"NO\n";
				return;
			}
		}
	}
	cout<<"YES\n";
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
}

```

---

## 作者：thedyingkai (赞：0)

### 思路
本题要求将小球从左侧或上侧推入，当且仅当已存在的小球的上方或左方推来小球时，小球才会移动，这说明每个没在左侧或上侧边上的小球都是被其他球一路推过来的，即该球满足一下两种条件之一：
1. 该球所在行上，在该球左面塞满球。
2. 该球所在列上，在该球上面塞满球。

于是，我们可以先遍历目标状态的每一行，从左开始，如果是 $1$ 就把他标记为 $2$，表示该球可以存在于该位置，如果中途出现 $0$，则后面的小球都不能由左侧推来。

然后遍历列，和行同理，需要注意的是前边标记为 $2$ 的小球和未标记的小球是一样处理的。

在两次遍历结束后，若还有 $1$，则证明有的小球目标位置不能达到，完成本题。
### AC code
```cpp
#define YES std::cout<<"YES"<<endl
#define NO std::cout<<"NO"<<endl
#define rep(i,x,n) for(int i=x;i<=n;i++)
void solve(){
    int n,m;
    cin>>n>>m;
    char map[51][51];
    rep(i,1,n) cin>>map[i];
    bool c1=0,c2=0;
    rep(i,1,n){
        bool flg=0;
        rep(j,0,m-1){
            if(map[i][j]=='0') flg=1;
            if(map[i][j]=='1'&&!flg) map[i][j]='2';
        }
    }
    rep(i,0,m-1){
        bool flg=0;
        rep(j,1,n){
            if(map[j][i]=='0') flg=1;
            if((map[j][i]=='1'||map[j][i]=='2')&&!flg) map[j][i]='2';
        }
    }
    rep(i,1,n) rep(j,0,m-1) if(map[i][j]=='1'){
        NO;
        return;
    }
    YES;
}
```

---

## 作者：HetmesAskalana (赞：0)

## 题意描述
一个空棋盘，可以从上到下或从左到右推入小球，如果下一格有球会将其沿推动方向推一格。

给定棋盘最终状态，问能否通过不限次推入操作达成这个状态。

## 解答
~~一力降十会~~

由于 $nm$ 的总和不超过 $10000$，数据范围小的可怜，所以可以用一个简单的结论暴力一下。

- 如果一个球 $(x, y)$ 是从上面压下来的，那么它所在列的上方 $(i < x, y)$ 一定充满小球。

- 如果一个球 $(x, y)$ 是从左面压进去的，那么它所在列的左侧 $(x, j < y)$ 一定充满小球。

以上两个条件如果满足任意一个，说明这个球是合法的，否则可以认为这个球是凭空出现在这里的。

如果所有的球都是合法的，则 `Yes`，否则在找到不合法的球时直接 `No`。

总时间复杂度 $O(n^2m^2)$。
## 代码
```cpp
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
void solve(){
    int n, m; cin >> n >> m;
    vector<string> G(n);
    for(int i = 0; i < n; ++i) cin >> G[i];
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < m; ++j){
            if(G[i][j] == '1'){
                bool flag1 = true, flag2 = true;
                for(int k = i; k >= 0; --k) flag1 &= (G[k][j] == '1'); // 上方
                for(int k = j; k >= 0; --k) flag2 &= (G[i][k] == '1'); // 左方
                if(flag1 or flag2) continue;
                no; return;
            }
        }
    }
    yes;
    return;
}
```

---

