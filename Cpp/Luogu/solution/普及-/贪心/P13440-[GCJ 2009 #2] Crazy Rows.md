# [GCJ 2009 #2] Crazy Rows

## 题目描述

给定一个 $N \times N$ 的矩阵，矩阵中的元素仅为 $0$ 或 $1$。你可以交换矩阵中任意两行相邻的行。

你的目标是让矩阵中所有的 $1$ 都位于主对角线之下或在主对角线上。也就是说，对于每个 $X$，$1 \leq X \leq N$，第 $X$ 行中不能有 $1$ 出现在第 $X$ 列右侧的位置。

请你返回实现目标所需的最小行交换次数。

## 说明/提示

**限制条件**

- $1 \leq T \leq 60$

**小数据集（6 分）**

- $1 \leq N \leq 8$

**大数据集（10 分）**

- $1 \leq N \leq 40$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
2
10
11
3
001
100
010
4
1110
1100
1100
1000```

### 输出

```
Case #1: 0
Case #2: 2
Case #3: 4```

# 题解

## 作者：封禁用户 (赞：10)

# [P13440 [GCJ 2009 #2] Crazy Rows](https://www.luogu.com.cn/problem/P13440)
## 题目介绍：

给定一个 $N \times N$ 的矩阵，矩阵中的元素仅为 $0$ 或 $1$。

我们要通过交换矩阵中任意相邻的两行让矩阵中所有的 $1$ 都位于主对角线之下或在主对角线上，也就是每行的最右边的 $1$ 的位置不超过其行号。

求最小行交换次数。

## 分析做法：

**贪心**求解即可：

1. 预处理，用数组保存每一行最右边的 $1$ 的位置。
 
2. 对于每行 $i$，从当前行开始向下寻找第一个可以放在 $i$ 行的行 $j$。

3. 将行 $j$ 交换到行 $i$ 的位置，交换次数为 $j - i$。

奉上代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int k = 1; k <= T; ++k) {
        int n;
        cin >> n;
        int b[45];
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            b[i] = -1;
            for (int j = 0; j < n; ++j) {
                if (s[j] == '1') {
                    b[i] = j;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int t = i;
            for (int j = i; j < n; ++j) {
                if (b[j] <= i) {
                    t = j;
                    break;
                }
            }
            for (int j = t; j > i; --j) {
                swap(b[j], b[j-1]);
                ans++;
            }
        }
        cout << "Case #" << k << ": " << ans << endl;
    }
    return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：ikunTLE (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P13440)

### 思路

根据题目要求，不难想到一条性质：一行中起到决定性因素的是该行的最后一个 `1`。

对此，可以进行**贪心**操作：

- 另 $L_i$ 表示第 $i$ 行最后一个 `1` 的下标。
- 如果该行需要移动，则计算所需移动次数 $L_i-i$。
- 该行移动后，更新所有的该行移动时所经过的行。

时间复杂度 $\mathcal{O}(N^2)$，而 $N\le40$，可以通过此题。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=50;
char s[N][N];
int last[N];
bool flag[N];
int main(){
	int T=read();
	for(int t=1;t<=T;++t){
		memset(last,0,sizeof(last));
		memset(flag,0,sizeof(flag));
		int n=read();
		for(int i=1;i<=n;++i){
			scanf("%s",s[i]+1);
			for(int j=n;j>=1;--j)
				if(s[i][j]=='1'){
					last[i]=j;
					break;
				}
		}
		int ans=0;
		for(int i=1;i<=n;++i){
			int j=i;
			while(j<=n&&last[j]>i)
				++j;
			if(j>n)
				continue;
			ans+=j-i;
			int temp=last[j];
			for(int k=j;k>i;--k)
				last[k]=last[k-1];
			last[i]=temp;
		}
		printf("Case #%d: %d\n",t,ans);
	}
	return 0;
}
```

---

## 作者：true_kun (赞：2)

对于这样的交换，我们考虑贪心。

首先，我们发现每一行的 $1$ 是否合法只与这一行最右侧的那个 $1$ 的位置有关，我们开一个数组存储每一行最右侧的 $1$ 的下标即可。

紧接着，我们开始贪心，对于一行上下交换，我们选择令它的上面几行全部合法，那么它只需要考虑向下交换即可。不难想到，如果这一行最后的合法结果一定是由下面离它最近的一行合法的 $a_i$ 替代它的位置，所以我们直接向下找然后交换即可。

多测不清空？
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int a[50];
signed main(){
	int t;
	cin>>t;
	for(int k=1;k<=t;k++){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			a[i]=0;
			for(int j=1;j<=n;j++){
				char x;
				cin>>x;
				if(x=='1') a[i]=j;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]>i){
				int point;
				for(int j=i;j<=n;j++){
					if(a[j]<=i){point=j;break;}
				}
				for(int j=point;j>i;j--){
					swap(a[j],a[j-1]);
					ans++;
				}
			}
		}
		cout<<"Case #"<<k<<": "<<ans<<endl;
		//cout<<"Case #"<<k<<": "<<ans<<endl;
	}
	return 0;
} 
/*
Case #1: 0
*/
```

---

## 作者：Circle_Table (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13440)

简述题意：存在一个正方形矩阵，每次操作交换相邻两行，最后要使得矩阵中的 $1$ 全部处于主对角线上或它左边。\
主对角线是矩阵左上角与右下角两顶点的连线。题干中也说了，只有 $j \leq i$ 时，才有 $a_{i,j}=1$ 可以成立。

那么，我们可以记录某一行最右边 $1$ 的地址，从而那一行必不能处于所记录地址的上方。即若 $a_{i,j}=1$ 则原来第 $i$ 行最终处于第 $j$ 行或其下方。

至此思路就清晰了。感觉实现起来有点像冒泡排序，把第一个可以放在第一排的放过来后就跳到后面，一直到最后一排，此过程中统计答案即可。

## 代码如下

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int inf=0x3f3f3f3f;
const int N=44;
int T,n,f[N],ans;
char s[N];

signed main()
{
	scanf("%d",&T);
	for(ri qwq=1;qwq<=T;qwq++)
	{
		scanf("%d",&n);
		memset(f,0,sizeof(f));
		ans=0;//记得多测清空 
		
		for(ri i=1;i<=n;i++)
		{
			scanf("%s",s+1);//下标从1开始 
			for(ri j=n;j>=1;j--)
			{
				if(s[j]=='1')//从右往左遍历遇到的第一个'1'即为所求 
				{            //也算是小优化吧
					f[i]=j;break;
				} 
			}
		}
		for(ri i=1;i<=n;i++)
		{
			if(f[i]<=i)continue;//本身就满足 
			for(ri j=i+1;j<=n;j++)
			{
				if(f[j]<=i)
				{
					ans+=j-i;
					for(ri k=j;k>i;k--)
					{
						swap(f[k],f[k-1]);
					}
					break;
				}
			}
		}
		printf("Case #%d: %d\n",qwq,ans);
	}
	return 0;
}
```

感谢阅读。

---

## 作者：menkm2025 (赞：1)

# [P13440 [GCJ 2009 #2] Crazy Rows](https://www.luogu.com.cn/problem/P13440)  
## 题意：
给定一个 $N \times N$ 的矩阵，矩阵中的元素仅为 $0$ 或 $1$。你可以交换矩阵中任意两行相邻的行。  

你的目标是让矩阵中的每个 $1$ 的列号都不超过其行号。  

输出实现目标所需的最小行交换次数。  

---

## 做法：
题意要求**最小化**代价，所以可以使用**贪心**求解：   
1. 由于每一行只要最后一个 $1$ 的位置满足条件，它前面的就一定满足条件，所以我们只记录每一行**最后**一个 $1$ 的位置。  
2. 对于每一行 $i$，向下（因为上面都已经摆好了）找到可以放进 $i$ 且距离这它最近的行 $j$（因为要求代价最小）。  
3. 把它逐行交换至 $i$，代价 $j - i$。  

[AC Link](https://www.luogu.com.cn/record/226801536)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, a[100];
signed main() {
	cin >> t;
	for (int ss = 1; ss <= t; ss++) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			string s;
			cin >> s;
			a[i] = -1;
			for (int j = n - 1; j >= 0; j--)
				if (s[j] == '1') {
					a[i] = j + 1;
					break;
				}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int t = i;
			for (int j = i; j <= n; j++)
				if (a[j] <= i) {
					t = j;
					break;
				}
			for (int j = t; j > i; j--) {
				ans++;
				swap(a[j - 1], a[j]);
			}
		}
		cout << "Case #" << ss << ": " << ans << '\n';
	}
	return 0;
}
```

---

## 作者：x_Toi_QiQi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13440)。
## 解题思路：
这里用样例来带着大家看一看解题思路。
### 样例解释：
对于样例：

```
4
1110
1100
1100
1000
```
读完题，我们可以将题意转化为这样：改变后的第 $i$ 行最右边的 $1$ 的位置 $\leq i$。只要满足这个条件，就可以解决此题。

所以我们需要统计每一行最右边的 $1$ 的位置：

```
4
1110 -> 最右边的1位置为3
1100 -> 最右边的1位置为2
1100 -> 最右边的1位置为2
1000 -> 最右边的1位置为1
```

这个时候第一行最右边的 $1$ 的位置应该 $\leq 1$，满足此条件的只有现在的第 $4$ 行，要把第 $4$ 行交换到第 $1$ 行需要 $3$ 次。此时，矩阵变为：

```
1000
1110
1100
1100
```
现在要满足第 $2$ 行的最右边的 $1$ 的位置 $\leq 2$，可以满足此条件的只有现在的第 $3$ 行和第 $4$ 行，选择离第 $2$ 行最近的第 $3$ 行，将第 $2$ 行移动到第 $3$ 行要进行一次。此时矩阵变为：

```
1000
1100
1110
1100
```

此时，变化后的矩阵已经满足了题目要求，所以，一共需要 $3+1=4$ 次。

**注意**：改变了行位置的行要进行标记。标记了的行不能再次更改。

### 具体做法：
我们可以做一个预处理，处理每一行最右边 $1$ 的位置。然后我们就可以贪心。

**贪心策略**：在移动到第 $i$ 行时，找一个离第 $i$ 行最近的且满足要求的行，然后对当前状态做改变，然后累加数量，最后输出就可以了。

## code：

```
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl "\n"
#define pii pair <int, int>

int main() {
    int t; 
    cin >> t;
    
    for (int c = 1; c <= t; ++c) {
        int n;
        cin >> n;
        
        vector<string> m(n); // 矩阵
        vector<int> r(n);    // 每行最右1的位置
        
        // 预处理每行最右1的位置
        for (int i = 0; i < n; ++i) {
            cin >> m[i];
            int p = 0; // 当前行最右1的位置
            for (int j = 0; j < n; ++j) {
                if (m[i][j] == '1') p = j + 1;
            }
            r[i] = p;
        }
        
        int s = 0; // 总交换次数
        vector<bool> u(n, false); // 标记行是否已使用
        
        // 贪心选择每行
        for (int i = 1; i <= n; ++i) {
            int j = 0;
            while (u[j] || r[j] > i) ++j; // 找到第一个未使用且满足条件的行
            
            // 计算选中行在剩余行中的位置
            int k = 0;
            for (int l = 0; l < j; ++l) {
                if (!u[l]) ++k;
            }
            
            s += k; // 累加交换次数
            u[j] = true; // 标记行已使用
        }
        
        cout << "Case #" << c << ": " << s << endl;
    }
    
    return 0;
}
```

---

## 作者：Lionel_Messi_10 (赞：1)

不难发现，输入的每行的最后一个 $1$ 的位置决定了该行在最终矩阵中的位置上限。对于第 $i$ 行，其最后一个 $1$ 的位置必须 $≤i$。

考虑使用贪心：

1. 从第 $1$ 行开始，逐行确定其应放置的原始行。

2. 对于目标行 $i$，在所有尚未放置的行中，找到最后一个 $1$ 的位置 $≤i$ 且当前行号最小的行。

3. 将该行通过相邻交换移动到第 $i$ 行，移动次数为当前行号与 $i$ 的差值。

4. 移动后，更新其他行的位置：所有在第 $i$ 行到该行原位置之间的行向下移动一行。

Code:

```cpp
/*
Problem: P13440 [GCJ 2009 #2] Crazy Rows
Author: Lionel_Messi_10
Time: 2025/7/25
*/
#include <bits/stdc++.h>
using namespace std;
#define __MADE return
#define IN 0
#define CHINA__ ;
#define cinvec(x, y, vec) cin>>x>>y;vec[y].push_back(x),vec[x].push_back(y);
#define coutvec(vec) for(auto i:vec)cout<<i<<' ';
#define endl '\n'
#define int long long
#define fi first
#define se second
#define pb emplace_back
#define size(s) (int)s.size()
#define filein(s) freopen(s,"r",stdin);
#define fileout(s) freopen(s,"w",stdout);
#define x1 x114514
#define x0 x1919810
#define y1 y114514
#define y0 y1919810
typedef pair<string, int> psi;
typedef pair<int, int> pii;
typedef pair<string, string> pss;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<string, string> mss;
const int N = 45;
string a[N];
int n, lst[N], pos[N];
void solve()
{
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++)
	{
		lst[i] = -1;
		for (int j = n - 1; j >= 0; j--)
		{
			if (a[i][j] == '1')
			{
				lst[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < n; i++) pos[i] = i;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int mn = n + 1, k = -1;
		for (int j = 0; j < n; j++)
		{
			if (pos[j] < i) continue;
			if (lst[j] <= i && pos[j] < mn)
			{
				mn = pos[j];
				k = j;
			}
		}
		if (k == -1) continue;
		ans += mn - i;
		for (int j = 0; j < n; j++)
		{
			if (j == k) continue;
			if (pos[j] >= i && pos[j] < mn) pos[j]++;
		}
		pos[k] = i;
	}
	cout << ans << endl;
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	int t = 1;
	while (T--)
	{
		cout << "Case #" << t << ": ";
		solve();
		t++;
	}
	__MADE IN CHINA__
}
```

---

## 作者：chen_zhe (赞：0)

本题解来自于[《挑战程序设计竞赛》](https://www.luogu.com.cn/training/813583)。

---

最先想到的是尝试所有 $N!$ 种交换方案。但在 Large 中，由于最大的 $N=40$，这当然是行不通的。

暂且先考虑一下最后应该把哪一行交换到第 1 行。最后的第 1 行应该具有 $00 \ldots 0$ 或是 $10 \ldots 0$ 的形式。可以交换到第 1 行的行当然也可以交换到第 2 及之后的行，当有多个满足条件的行时，选择离第 1 行近的行对应的最终费用要小。大家肯定都已注意到了这一点吧。有兴趣的读者不妨自己证明一下。

确定第 1 行之后，就没有必要再移动它了，于是对于之后的行就可以以同样的思路处理。

在这道题中，每行的 0 和 1 的位置并不重要，只要知道每行最后一个 1 所在的位置就足够了。如果先将这些位置预先计算好，那么就能降低行交换时的复杂度。直接按矩阵的形式处理的复杂度是 $O(N^{3})$，而预先计算后再处理的复杂度降为 $O(N^{2})$。

```cpp
// 输入
int N;
int M[MAX_N][MAX_N];  // 矩阵

int a[MAX_N];  // a[i]表示第i行最后出现的1的位置——1~n-1

void solve() {
    int res = 0;
    for (int i = 0; i < N; i++) {
        a[i] = -1;  // 如果第i行不含1的话，就当作-1
        for (int j = 0; j < N; j++) {
            if (M[i][j] == 1) a[i] = j;
        }
    }
    for (int i = 0; i < N; i++) {
        int pos = -1;  // 要移动到第i行的行
        for (int j = i; j < N; j++) {
            if (a[j] <= i) {
                pos = j;
                break;
            }
        }

        // 完成交换
        for (int j = pos; j > i; j--) {
            swap(a[j], a[j - 1]);
            res++;
        }
    }
    printf("%d\n", res);
}
```

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13440)  
给定一个 $N \times N$ 的 01 矩阵，通过交换相邻的行，使得所有 `1` 必须位于第 $X$ 列或其左侧，求出最小的相邻行交换次数。

### 题目分析
我们预处理每一行最右边 $1$ 的位置：对于每一行 $i$，计算其最右边 $1$ 的位置 $r_i$。如果一行全为 $0$，设 $r_i = 0$。然后依次处理每一行 $i$，找到一个未被使用的行 $k$（$k \geq i$），其 $r_k \leq i$，然后将该行通过相邻交换移动到第 $i$ 行。交换次数为 $k - i$，模拟交换过程即可。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void f(int t){
	int n;
	cin>>n;
	vector<string>s(n);
	for(int i=0;i<n;i++){
		cin>>s[i];
	}
	vector<int>r(n);
	for(int i=0;i<n;i++){
		int pos=-1;
		for(int j=0;j<n;j++){
			if(s[i][j]=='1')pos=j;
		}
		r[i]=pos+1;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int flag=-1;
		for(int j=i-1;j<n;j++){
			if(r[j]<=i){
				flag=j;
				break;
			}
		}
		ans+=flag-i+1;
		int tmp=r[flag];// 模拟交换过程
		for(int j=flag;j>i-1;j--){
			r[j]=r[j-1];
		}
		r[i-1]=tmp;
	}
    cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	int y;
	cin>>y;
	for(int i=1;i<=y;i++){
		f(i);
	}
	return 0;
}
```

---

