# Satyam and Counting

## 题目描述

Satyam is given $ n $ distinct points on the 2D coordinate plane. It is guaranteed that $ 0 \leq y_i \leq 1 $ for all given points $ (x_i, y_i) $ . How many different nondegenerate right triangles $ ^{\text{∗}} $ can be formed from choosing three different points as its vertices?

Two triangles $ a $ and $ b $ are different if there is a point $ v $ such that $ v $ is a vertex of $ a $ but not a vertex of $ b $ .

 $ ^{\text{∗}} $ A nondegenerate right triangle has positive area and an interior $ 90^{\circ} $ angle.

## 说明/提示

The four triangles in question for the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2009D/34af5d1e01dabd5b071d413da74fdbeb85cca657.png)

## 样例 #1

### 输入

```
3
5
1 0
1 1
3 0
5 0
2 1
3
0 0
1 0
3 0
9
1 0
2 0
3 0
4 0
5 0
2 1
7 1
8 1
9 1```

### 输出

```
4
0
8```

# 题解

## 作者：coderJerry (赞：5)

分类讨论题。

[样例第一组测试数据的动图，可以查看帮助理解](https://espresso.codeforces.com/e22fad0d3e6b03380f52e36e0bd2a38032373572.png)（如果图挂了到 CF 上看）。
#
- case 1：两条直角边垂直于两坐标轴的，
  
这个时候其中一条直角边的两端点必定是 $(t,0),(t,1)$。另外 $n-2$ 个点都能和这条线段组成直角三角形。

- case 2：45 度的等腰直角三角形，且两条直角边都不垂直于坐标轴的，

 - - 直角顶点是 $(t,0)$，
   - 这个时候另外两个顶点就必定是 $(t-1,1),(t+1,1)$。
 - - 同理，当直角顶点是 $(t,1)$ 时，
   - 这个时候另外两个顶点就必定是 $(t-1,0),(t+1,0)$。

枚举每个点是否符合上述情况，统计即可。
#
[清空不彻底，被hack两行泪！](https://www.luogu.com.cn/discuss/969102)

赛时代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int v[200010][2];//v[x][y] 表示 (x,y) 是否出现过
signed main(){
    int t,x,y,n,ans=0;
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        for(int i=0;i<=200000;i++){v[i][0]=v[i][1]=0;}//清空不彻底，被hack两行泪！
        for(int i=1;i<=n;i++){
            cin>>x>>y;
            v[x][y]=1;
        }
        for(int i=0;i<=n;i++){
            if(v[i][0]==1&&v[i][1]==1)ans+=(n-2);//case1
            if(v[i][1]==1&&v[i-1][0]==1&&v[i+1][0]==1)ans++;//case2-1
            if(v[i][0]==1&&v[i-1][1]==1&&v[i+1][1]==1)ans++;//case2-2
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

若点 $(i,0),(i,1)$ 同时存在，那么剩下的 $n-2$ 个点都能与它们产生贡献。还有两种能做贡献的情况是 $(i,0),(i+2,0),(i+1,1)$ 与 $(i,1),(i+2,1),(i+1,0)$。

---

## 作者：_H17_ (赞：0)

## 题目分析

定义：“$x$ 是竖线”表示 $(x,0),(x,1)$ 都被标记；“斜三角”表示 $(x,y),(x-1,y\oplus 1),(x+1,y\oplus 1)$ 组成的三角形。（注：以上定义都有作者胡编乱造，只是为了方便描述）

显然三角形分为两种：竖线的和斜三角。

竖线：对于每个竖线和出他们两个点以外的任意一点都可以组成三角形，假设竖线有 $k$ 个，则对答案的贡献是 $k\times(n-2)$。

斜三角：对于每个点，暴力判断即可（用 `map` 维护位置有无标记）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,x[300001],y[300001],sum,ans;
map<int,int>mp;
map<pair<int,int>,int>p;
void Main(){
    mp.clear(),p.clear();
    sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        mp[x[i]]++;
        if(mp[x[i]]==2)
            sum++;
        p[{x[i],y[i]}]=1;
    }
    ans=sum*(n-2);
    for(int i=1;i<=n;i++)
        ans+=(p[{x[i]-1,y[i]^1}]&&p[{x[i]+1,y[i]^1}]);
    cout<<ans<<'\n';
    return;
}
signed main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

## 作者：cly312 (赞：0)

比较容易观察的一道题，但是场上不开 long long 见[祖宗](https://codeforces.com/contest/2009/submission/279575736)了。

由于这题的 $x$ 最大值比较小，所以我们可以直接存每个坐标是否有点。

有两种三角形符号条件：

- 存在两个点 $(x,0),(x,1)$，可以观察到任意的其它点都可以成为第三点。
- 有三个点为 $(x,0),(x+1,1),(x+2,0)$ 或 $(x,1),(x+1,0),(x+2,1)$，可以观察到这是一个腰为 $\sqrt 2$ 的等腰直角三角形。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool e[200005][2];
signed main(){
    int t;
    cin>>t;
    while(t--){
    	memset(e,0,sizeof e);
    	int n;
    	cin>>n;
    	vector<pair<int,int>> g(n+1);
    	for(int i=1;i<=n;i++){
    		cin>>g[i].first>>g[i].second;
    		e[g[i].first][g[i].second]=1;
		}	
		int ans=0,ans2=0;
		for(int i=1;i<=n;i++){
			if(e[g[i].first][0]&&e[g[i].first][1]){
				ans+=n-2;
			}
			if(e[g[i].first+1][!g[i].second]&&e[g[i].first+2][g[i].second]) ans2++;
		}
		cout<<ans/2+ans2<<endl;
	}
	return 0;
}
```

---

