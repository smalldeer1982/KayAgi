# [JOI 2019 Final] 勇者比太郎 / Bitaro the Brave

## 题目描述

勇者比太郎正在面对恶魔。

为了攻击恶魔，比太郎会在一个 $H\times W$ 的网格上放置三种道具（分别记作 `J,O,I`）并施放咒语。网格上往下数第 $i$ 行 $(1\le i\le H)$，左往右数第 $j$ 列 $(1\le j\le W)$ 的格子坐标记为 $(i,j)$。

现在，比太郎在网格的每个格子中放置了三种道具中的一种，比太郎将施放一个咒语，其威力取决于三种道具的排列方式。具体的，威力大小等于满足以下条件的有序四元组 $(i,j,k,l)$，满足 $(1\le i<k\le H,1\le j<l\le W)$ 的数量。

条件：$(i,j)$ 位置的格子上的道具为 `J`，$(i,l)$ 位置上的道具为 `O`，$(k,j)$ 位置上的道具为 `I`。

比太郎想知道他的咒语的威力是多少。

请写一个程序，根据三种道具在网格上的排列，计算出咒语的威力（即满足上述条件的四元组数量）。

## 说明/提示

【数据范围与约定】

- $ 2 \le H \le 3000 $。
- $ 2 \le W \le 3000 $。

1. 对于 $20 \%$ 的数据，$ H \le 100,W \le 100 $。
2. 对于 $30 \%$ 的数据，$ H \le 500,W \le 500 $。
3. 对于 $50 \%$ 的数据，无特殊限制。

## 样例 #1

### 输入

```
3 4
JOIJ
JIOO
IIII```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
JJOO
JJOO
IIJO
IIIJ```

### 输出

```
17```

# 题解

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11788)
## 涉及知识
- 预处理——前缀和。
## 思路
暴力，时间复杂度 $O(H^2W^2)$，因为数据范围是 $2 \le H,W \le 3000$，显然无法通过。

大胆猜一下，正解时间复杂度应该为 $O(HW)$。

读题易知，这题需要**前缀和预处理**。输入后计算一下，部分代码如下：

```cpp
for(int i=1;i<=H;i++)
    for(int j=W;j>=1;j--)
        sum_O[i][j]=sum_O[i][j+1]+(a[i][j]=='O');
for(int j=1;j<=W;j++)
    for(int i=H;i>=1;i--)
        sum_I[i][j]=sum_I[i+1][j]+(a[i][j]=='I');
```
其中 `sum_O[i][j]` 表示对于第 $i$ 行中第 $j$ 列到第 $W$ 列中 `O` 的数量。`sum_I[i][j]` 表示对于第 $j$ 列中第 $i$ 行到第 $H$ 行中 `I` 的数量。
 
预处理结束，开始操作求值。

对于每个 $1 \le i \le H$ 和 $1 \le j \le W$，若 $a_{i,j}$ 是 `J`，则累加答案。不难发现，答案就是  $sum\_O[i][j] \times sum\_I[i][j]$。

注意：十年 OI 一场空，不开 **long long** 见祖宗。求值时注意要开 **long long**！

思路分析好了，相信聪明的你一定会写代码了吧？
## 完整 AC 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
const int N=3005;
int H,W,sum_O[N][N],sum_I[N][N],ans;
char a[N][N];
signed main(){
	scanf("%lld%lld",&H,&W);
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
			cin>>a[i][j];
    for(int i=1;i<=H;i++)
		for(int j=W;j>=1;j--)
			sum_O[i][j]=sum_O[i][j+1]+(a[i][j]=='O');
	for(int j=1;j<=W;j++)
		for(int i=H;i>=1;i--)
			sum_I[i][j]=sum_I[i+1][j]+(a[i][j]=='I');
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
			if(a[i][j]=='J') ans+=sum_O[i][j]*sum_I[i][j];
	printf("%lld",ans);
    return 0;   
}
```

最后，我提出一个疑问：为啥 `JOI` 这类题总是如此雷同啊？

---

## 作者：DevilsFlame (赞：4)

最初，我们不难想到暴力，时间复杂度 $O(n^2m^2)$，显然不对，于是想着更优解。

对于题目所说的四元组，联想到所学的前缀和，便想着如何用前缀和求解。

对于 $i,j$ 显然是要枚举的，那么我们就要想如何预处理出 ```O``` 和 ```I``` 的个数。

我们可以利用前缀和从后往前累计 ```O``` 和 ```I``` 的数量，我们定义为 ```O[i][j] 和 I[i][j]```，学过组合数学的人知道对于 $i,j$ 的答案就是 $O[i][j] \times I[i][j]$。

由此得到以下代码：

```cpp
#include<bits/stdc++.h>
#define N 3010
#define int long long//莫忘开long long，否则20pts
using namespace std;
char s[N][N];
int n,m,ans,O[N][N],I[N][N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i ++)
	for(int j = 1;j <= m;j ++) cin >> s[i][j];
	for(int i = 1;i <= n;i ++)
	for(int j = m;j;j --)//处理O[i][j]
	{
		O[i][j] = O[i][j + 1];
		if(s[i][j] == 'O') O[i][j] ++;
	}
	for(int j = 1;j <= m;j ++)
	for(int i = n;i;i --)//处理I[i][j]
	{
		I[i][j] = I[i + 1][j];
		if(s[i][j] == 'I') I[i][j] ++;
	}
	for(int i = 1;i <= n;i ++)
	for(int j = 1;j <= m;j ++) if(s[i][j] == 'J') ans += O[i][j] * I[i][j];
	cout << ans << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P11788)

用前缀和的思想来做。

对于每一行 $i$，统计从第 $j$ 列到第 $W$ 列中 `O` 的数量，记为 $a_{i,j}$；再对于每一列 $j$，统计从第 $i$ 行到第 $H$ 行中 `I` 的数量，记为 $b_{i,j}$。然后遍历每个 `J`，通过 $a_{i,j+1}$ 得到这一行中 `J` 右侧的 `O` 的数量，再通过 $b_{i+1,j}$ 得到这一列中 `J` 的下方的 `I` 的数量，两者相乘求和即可。

时间复杂度 $\Theta(HW)$。

```cpp
#include <iostream>
#define int long long
using namespace std;

const int N = 3005;

string s[N];
int a[N][N], b[N][N];

signed main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	for (int i = 0; i < n; i++)
		for (int j = m - 1; j >= 0; j--)
			a[i][j] = a[i][j + 1] + (s[i][j] == 'O');
	for (int j = 0; j < m; j++)
		for (int i = n - 1; i >= 0; i--)
			b[i][j] = b[i + 1][j] + (s[i][j] == 'I');
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (s[i][j] == 'J') ans += a[i][j + 1] * b[i + 1][j];
	cout << ans;
	return 0;
}
```

---

## 作者：Frozen_Ladybug (赞：1)

这道题如果用暴力模拟的话，复杂度为 $\Omicron(n^2m^2)$，不足以通过时限。

那么考虑优化，用前缀和差分的方式，可以将复杂度调整至 $\Omicron(nm)$，可以通过。

对于第 $i$ 行，考虑从第 $j$ 至 $m$ 列中 ```O``` 的数量，记为 $c_{0}(i,j)$；对于第 $j$ 列，考虑从第 $i$ 至 $n$ 列中 ```I``` 的数量，记为 $c_{1}(i,j)$。

遍历每个 ```J```，记录 ```J``` 右侧 ```O``` 的数量和 ```J``` 下方 ```I``` 的数量；将 $c_0$ 和 $c_1$ 相乘求和记为所求。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c[2][3005][3005];
char s[3005][3005];
long long ans;
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=m;j;j--)
            c[0][i][j]=c[0][i][j+1]+(s[i][j]=='O');
    for(int j=1;j<=m;j++)
        for (int i=n;i;i--)
            c[1][i][j]=c[1][i+1][j]+(s[i][j]=='I');
    for (int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans+=(s[i][j]=='J')*c[0][i][j]*c[1][i][j];
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：liuyuantao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11788)  
根据题意，我们要求出使得 ```O``` 在 ```J``` 的右方，```I``` 在 ```J``` 的下方的三元组 $(J,O,I)$ 组数。  
考虑枚举 ```J```。只要我们统计出 ```J``` 右方的 ```O``` 个数 $dpo_{i,j}$ 及其下方的 ```I``` 个数 $dpi_{i,j}$，那么根据乘法原理，这个位置的 ```J``` 对于答案的贡献即为 $dpo_{i,j} \times dpi_{i,j}$。  
显然有以下关系:  
$dpo_{i,j}=dpo_{i,j+1}+[(i,j)=O]$，  
$dpi_{i,j}=dpi_{i+1,j}+[(i,j)=I]$。  
于是我们预处理时从右到左计算 $dpo$，从下到上计算 $dpi$ 即可。注意边界。  
时间复杂度 $O(HW)$。  
[AC记录](https://www.luogu.com.cn/record/205073052)   


```cpp
#include <bits/stdc++.h>

using namespace std;

const int N=3e3+5;
int n,m;
int dpo[N][N],dpi[N][N];
long long ans=0;
char c[N][N];

int main(){
    ios::sync_with_stdio();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            dpo[i][j]=dpo[i][j+1];
            if(c[i][j]=='O')dpo[i][j]++;
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
            dpi[i][j]=dpi[i+1][j];
            if(c[i][j]=='I')dpi[i][j]++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]=='J'){
                ans+=dpo[i][j]*dpi[i][j];
            }
        }
    }
    cout<<ans<<endl;
    
    return 0;
}
```

---

## 作者：yanmingqian (赞：0)

~~怎么又是统计 JOI 数量类似题目，和[这题](https://www.luogu.com.cn/problem/AT_joi2016ho_b)神韵相似。你们 JOI 出题都这个样吗？~~

~~话说那题我也写题解了欸。~~

显然对于每一个 J，我们后缀统计同行在其右的 O 的个数和同列在其下的 I 的个数，二者相乘即可。

代码：

```cpp
#include<iostream>
using namespace std;
char c[3010][3010];
int s1[3010][3010],s2[3010][3010];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
		}
	} 
	long long ans=0;
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
            s1[i][j]=s1[i][j+1]+(c[i][j]=='O');
            s2[i][j]=s2[i+1][j]+(c[i][j]=='I');
			if(c[i][j]=='J'){
				ans+=s1[i][j]*s2[i][j];
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FamousKillerconan (赞：0)

## 思路
观察题目中的要求，可以转化为：对于每一个 ```J```，计算它同一行且列坐标大于它的 ```O``` 和它同一列且行坐标大于它的 ```I``` 的点对数数。


我们用前缀和来计算某一个矩阵中 ```O``` 和 ```I``` 的个数。


AC 代码：


```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=3e3+5;
const int INF=0x3f3f3f3f;
const double EPS=10e-6;
const int MOD=1e9+7;
int n,m,ans,sumJ[N][N],sumO[N][N],sumI[N][N];
char mp[N][N];
int calc(int x,int y,int xx,int yy,int op){
	if(op==1)return sumO[xx][yy]-sumO[xx][y-1]-sumO[x-1][yy]+sumO[x-1][y-1];
	if(op==2)return sumI[xx][yy]-sumI[xx][y-1]-sumI[x-1][yy]+sumI[x-1][y-1];
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			sumJ[i][j]=sumJ[i-1][j]+sumJ[i][j-1]-sumJ[i-1][j-1]+(mp[i][j]=='J');
			sumO[i][j]=sumO[i-1][j]+sumO[i][j-1]-sumO[i-1][j-1]+(mp[i][j]=='O');
			sumI[i][j]=sumI[i-1][j]+sumI[i][j-1]-sumI[i-1][j-1]+(mp[i][j]=='I');
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='J'){
				int cntO=calc(i,j+1,i,m,1);
				int cntI=calc(i+1,j,n,j,2);
				ans+=cntO*cntI;
			//	cout<<cntO<<" "<<cntI<<endl; 
			}
		}
	}
	cout<<ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

运用简单乘法原理，容易发现对于每个 `J`，以它为左上角，以 `O` 为右上角，以 `I` 为左下角的矩形个数就是这个 `J` 的正下方的 `I` 的个数乘上这个 `J` 的正右边的 `O` 的个数，使用两个数组分别存储每个位置上正下方的 `I` 的个数和正右边的 `O` 的个数，再对于每个 `J` 计算贡献即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[3005][3005];
int f1[3005][3005];
int f2[3005][3005];
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            int x=0;
            if(a[i][j]=='O') x=1;
            f1[i][j]=f1[i][j+1]+x;
        }
    }
    for(int j=1;j<=m;j++)
    {
        for(int i=n;i>=1;i--)
        {
            int x=0;
            if(a[i][j]=='I') x=1;
            f2[i][j]=f2[i+1][j]+x;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]=='J')
                ans+=f1[i][j]*f2[i][j];
    cout<<ans;
    return 0;
}
```

---

## 作者：MonKeySort_ZYczc (赞：0)

说句闲话：不至于黄吧。  
## 思路流程
看懂题目这道题就比较轻松了。  
根据定义，对于每个`J`，只要用该点正下方的`I`的数量与正右方`O`的数量的积就可以求出该点所求点集的数量。  
可是直接枚举一眼超时，我们便可以用一个常用的算法思想——前缀和优化复杂度。  
也就是说，设 $I_{i,j}$ 为 $(i,j)$ 这一点正右边（包括本身）`I`的数量之和，$O_{i,j}$ 为 $(i,j)$ 这一点正下方（包括本身）`O`的数量之和，$C_{i,j}$ 为 $(i,j)$ 这一点的字符。  
那么此时：

- 考虑 $I_{i,j}$：
  - 若 $C_{i,j}$ 为 `I`：$I_{i,j}=I_{i,j+1}+1$。
  - 否则：$I_{i,j}=I_{i,j+1}$。
- 再考虑 $O_{i,j}$：
  - 若 $C_{i,j}$ 为 `O`：$O_{i,j}=O_{i+1,j}+1$。
  - 否则：$O_{i,j}=O_{i+1,j}$。
 
最后统计即可。  
总时间复杂度：$O(HW)$。  

提醒几句：
- 注意循环顺序。
- 虽然没试过，但正如那句古语：“十年 OI 一场空，不开 `long long`见祖宗。”，请在统计时开 `long long`。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3114;
int h,w,O[N][N],I[N][N];
char c[N][N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>h>>w;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++) cin>>c[i][j];
		for(int j=w;j>=1;j--) O[i][j]=O[i][j+1]+(c[i][j]=='O');
	}
	for(int j=1;j<=w;j++)
	{
		for(int i=h;i>=1;i--) I[i][j]=I[i+1][j]+(c[i][j]=='I');
	}
	long long ans=0;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			if(c[i][j]=='J') ans+=O[i][j]*I[i][j];
		}
	}
	cout<<ans;
}

```

---

## 作者：lvweisi (赞：0)

这题就是一道水题，注意到如果当前这个点是 $J$ ，就把 $ans$ 加上这一行是 $I$ 的个数与这一列是 $O$ 的个数的乘积。

既:
```cpp
ans+=(O[i][m]-O[i][j])*(I[n][j]-I[i][j]);
```
时间复杂度为 $O(nm)$ 刚好能过。

### 代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3005][3005];
long long I[3005][3005],O[3005][3005];
int n,m;
int main() {
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];
			if(a[i][j]=='O')O[i][j]=O[i][j-1]+1;
			else O[i][j]=O[i][j-1];
			if(a[i][j]=='I')I[i][j]=I[i-1][j]+1;
			else I[i][j]=I[i-1][j];//计算前缀 
		}
	}
	long long ans=0;//记得开long long!!! 
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(a[i][j]=='J'){//枚举每一个J 
				ans+=(O[i][m]-O[i][j])*(I[n][j]-I[i][j]);
			}
		} 
	}
	cout<<ans;
	return 0;
}
```
再次强调，这题一定要开 ```long long``` ，不然只有20分!!!

---

