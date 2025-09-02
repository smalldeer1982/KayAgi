# Homework

## 题目描述

今天Peter有一项额外的作业：老师给定三个字母 $n,m,k,$ 需要在一个 $n\times m$ 的网格当中标记一些方格。要求至少要标记一个方格，标记的所有方格必须形成一个联通块，且标记的方格中必须恰好包含 $k$ 个"L"形（即在一个2*2的方格中标记了3个方格所形成的图形）。

Peter不能完成这项作业，因此向你求助。请帮助他构造出这样的一个图形。

## 样例 #1

### 输入

```
3
3 3 4
3 3 5
3 3 3
```

### 输出

```
.*.
***
.*.

**.
**.
*..

.*.
***
*..
```

# 题解

## 作者：KaguyaH (赞：3)

> 一张 $n \cdot m$ 的网格中标记若干格子，使得标记的格子形成 $k$ 个 L 形。
>
> L 形是 $2 \times 2$ 的区域中的 $3$ 个格子。
>
> 多组数据。$1 \le t \le 100$，$3 \le n, m, nm, \sum nm \le 10^5$。

一行一行标记，直到无法继续。若此时组成的 L 形数目恰为 $k$ 则找到了一组解；若所有格子均被标记则无解。

在下一行一格一格标记，直到无法继续。当前行必然有格子被标记且有格子未被标记。易得此时还需组成的 L 形数目（记为 $r$）少于 $4$。

记网格第 $i$ 行第 $j$ 列的格子为 $(i, j)$。记首个未被标记的格子为 $(x, y)$。

1. $r = 1$。
   1. $y < m$。可标记 $(x, m)$。
   2. $y = m$。
      1. $x = n$。无解（当前方案是除全部标记外组成 L 形最多的方案）。
      2. $x < n$。可标记 $(x + 1, 1)$。
2. $r = 2$。
   1. $y < m - 1$。可标记  $(x, m - 1)$。
   2. $y = m - 1$。
      1. $x = n$。无解（当前方案是组成 L 形不多于 $k$ 的最多方案）。
      2. $x < n$。
         1. $m = 3$。可标记 $(x + 1, 1), (x + 1, 2), (x, m)$。
         2. $m > 3$。可标记 $(x + 1, 2), (x, m)$。
   3. $y = m$。
      1. $x = n$。无解（当前方案是除全部标记外组成 L 形最多的方案）。
      2. $x < n$。可标记 $(x + 1, m - 1), (x + 1, m)$。
3. $r = 3$。
   1. $y < m - 2$。可标记 $(x, m - 2), (x, m)$。
   2. $y = m - 2$。
      1. $x = n$。
         1. $n = 3$。可撤销标记 $(1, m), (2, m)$ 并标记 $(x, y), (x, y + 1)$。
         2. $n > 3$。无解。组成 L 形多于当前方案，且少于当前方案与 $(x, y)$ 的并的方案仅有一种，即除 $(n, m), (n, m - 1), (n - 1, m)$ 外全部标记，且易于证明该方案亦不能使组成 L 形数恰为 $k$。
      2. $x < n$。
         1. $m = 4$。可标记 $(x, m - 1), (x + 1, 1), (x + 1, 2)$。
         2. $m > 4$。可标记 $(x, m - 1), (x + 1, 1)$。
   3. $y = m - 1$。
      1. $m = 3$。可标记 $(x, m), (x + 1, 1), (x + 1, 2), (x + 1, 3)$。
      2. $m > 3$。可标记 $(x, m), (x + 1, m), (x + 1, m - 1), (x + 1, 1)$。
   4. $y = m$。易于证明该情况不存在。

时间复杂度 $O(\sum nm + t)$。空间复杂度 $O(\sum nm)$。

代码中编号区间为 $[0, n) [0, m)$，与题解中略有不同。若仍有不同之处当为作者疏忽，请联系作者并以代码为准。

```cpp
namespace Main::Main {
  namespace Main {
    static lu n, m, k; static bool** a;
    static inline bool solve() {
      lu cnt{}; fill(a[0], a[0] + m, true); lu i(1); while (i < n and cnt + 4 * (m - 1) <= k) fill(a[i], a[i] + m, true), cnt += 4 * (m - 1), ++i;
      ; if (cnt == k) return true; if (i == n) return false;
      // fputs("104\n", stderr);
      a[i][0] = true, ++cnt; lu j(1); while (j < m and cnt + 4 <= k) a[i][j] = true, cnt += 4, ++j; if (cnt == k) return true;
      // fputs("106\n", stderr); fprintf(stderr, "%lu %lu\n", i, j);
      switch (k - cnt) {
      case 1: if (j < m - 1) { a[i][m - 1] = true, ++cnt; break; } if (i < n - 1) { a[i + 1][0] = true, ++cnt; break; } break;
      case 2:
        if (j < m - 2) { a[i][m - 2] = true, cnt += 2; break; } if (i == n - 1) break;
        if (j == m - 2) if (m == 3) a[i + 1][1] = a[i + 1][0] = a[i][m - 1] = true, cnt += 2; else a[i + 1][0] = a[i][m - 1] = true, cnt += 2;
        else a[i + 1][m - 1] = a[i + 1][m - 2] = true, cnt += 2;
        break;
      case 3:
        if (j < m - 3) { a[i][m - 1] = a[i][m - 3] = true, cnt += 3; break; }
        if (i == n - 1) {
          if (i == 2 and j == m - 3) a[i - 1][m - 1] = a[i - 2][m - 1] = false, a[i][j + 1] = a[i][j] = true, cnt += 3;
          break;
        }
        if (j == m - 3) if (m == 4) a[i + 1][1] = a[i + 1][0] = a[i][m - 2] = true, cnt += 3; else a[i + 1][0] = a[i][m - 2] = true, cnt += 3;
        else
          if (m == 3) /*fputs("3.3.0\n", stderr),*/ a[i][m - 1] = true, fill(a[i + 1], a[i + 1] + m, true), cnt += 3;
          else a[i + 1][0] = a[i + 1][m - 2] = a[i + 1][m - 1] = a[i][m - 1] = true, cnt += 3;
        break;
      }
      return cnt == k;
    }
    static inline void main() {
      io >> n >> m >> k, a = new bool*[n]; for (lu i{}; i < n; ++i) a[i] = new bool[m], memset(a[i], 0x00, m * sizeof(bool));
      ; if (solve()) for (lu i{}; i < n; putchar('\n'), ++i) for (lu j{}; j < m; ++j) putchar(a[i][j] ? '*' : '.'); else puts("-1"); putchar('\n');
      ; for (lu i{}; i < n; ++i) delete[]a[i]; delete[]a;
    }
  }
  static hu t; static inline void main() { get(t); for (hu i{}; i < t; ++i) Main::main(); }
}
```

[Submission](https://codeforces.com/contest/720/submission/134939358).

---

## 作者：Melancholy_ (赞：0)


**思路：**

这道构造题思路十分简单——按题意暴搜即可。

但是有很多小细节：

为了判无解我们需要记录一个搜索深度 `dep`，如果 `dep` 大于了 $8\times n\times m$（放置“L”型的上限）那么就返回。

还有就是处理横竖边界的问题。为了处理边界，我们一开始需要把 $n$ 和 $m$ 中较大的赋给 $n$。然后在搜索的时候特殊处理边界。但是这样生成的矩阵横竖就反了，最后输出的时候还要特判一下。


```cpp
#include<bits/stdc++.h>
#define freo(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define ll long long
using namespace std;
const int maxn=4e4+5;
int n,m,k,dep,mp[maxn][505],flag1,flag2;
inline ll read()
{
	ll ret=0;char ch=' ',c=getchar();
	while(!(c<='9'&&c>='0')) ch=c,c=getchar();
	while(c<='9'&&c>='0') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
void dfs(int x,int y,int num)
{
	if(flag2) return;
	if((x>1||y>1)&&num==k)
	{
		flag2=1;
		if(!flag1)//特判输出
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
				{
					if(mp[i][j]) putchar('*');
					else putchar('.');
				}
				putchar('\n');
			}
		}
		else
		{
			for(int i=1;i<=m;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(mp[j][i]) putchar('*');
					else putchar('.');
				}
				putchar('\n');
			}
		}
		putchar('\n');
		return;
	}
	if(x==n+1) return;//特殊处理边界
	else if(y==m+1) dfs(x+1,1,num);//特殊处理边界
	else if(++dep>n*m) return;
	else
	{
		int tmp=0;
		if(mp[x-1][y]) tmp+=mp[x][y+1]+mp[x-1][y-1]+mp[x-1][y+1];
		if(mp[x+1][y]) tmp+=mp[x][y-1]+mp[x+1][y-1]+mp[x+1][y+1];
		if(mp[x][y-1]) tmp+=mp[x-1][y]+mp[x-1][y-1]+mp[x+1][y-1];
		if(mp[x][y+1]) tmp+=mp[x-1][y+1]+mp[x+1][y]+mp[x+1][y+1];
		if(num+tmp<=k&&(x==1||y==1||mp[x-1][y]||mp[x][y-1]))
		{
			mp[x][y]=1;
			dfs(x,y+1,num+tmp);
			mp[x][y]=0;
		}
		dfs(x,y+1,num);
	}
}
int main()
{
	int t=read();
	while(t--)
	{
		dep=0;flag1=0,flag2=0;
		memset(mp,0,sizeof(mp));
		n=read(),m=read(),k=read();
		if(n<m) swap(n,m),flag1=1;
		dfs(1,1,0);
		if(!flag2) printf("-1\n");
	}
	return 0;
}
```


---

