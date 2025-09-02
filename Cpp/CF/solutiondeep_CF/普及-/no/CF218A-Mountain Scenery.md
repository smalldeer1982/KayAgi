# 题目信息

# Mountain Scenery

## 题目描述

Little Bolek has found a picture with $ n $ mountain peaks painted on it. The $ n $ painted peaks are represented by a non-closed polyline, consisting of $ 2n $ segments. The segments go through $ 2n+1 $ points with coordinates $ (1,y_{1}) $ , $ (2,y_{2}) $ , $ ... $ , $ (2n+1,y_{2n+1}) $ , with the $ i $ -th segment connecting the point $ (i,y_{i}) $ and the point $ (i+1,y_{i+1}) $ . For any even $ i $ $ (2<=i<=2n) $ the following condition holds: $ y_{i-1}&lt;y_{i} $ and $ y_{i}&gt;y_{i+1} $ .

We shall call a vertex of a polyline with an even $ x $ coordinate a mountain peak.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF218A/96f9e39adc23f097d41530b53dba00529f48c7bd.png) The figure to the left shows the initial picture, the figure to the right shows what the picture looks like after Bolek's actions. The affected peaks are marked red, $ k $ = 2. Bolek fancied a little mischief. He chose exactly $ k $ mountain peaks, rubbed out the segments that went through those peaks and increased each peak's height by one (that is, he increased the $ y $ coordinate of the corresponding points). Then he painted the missing segments to get a new picture of mountain peaks. Let us denote the points through which the new polyline passes on Bolek's new picture as $ (1,r_{1}) $ , $ (2,r_{2}) $ , $ ... $ , $ (2n+1,r_{2n+1}) $ .

Given Bolek's final picture, restore the initial one.

## 样例 #1

### 输入

```
3 2
0 5 3 5 1 5 2
```

### 输出

```
0 5 3 4 1 4 2 
```

## 样例 #2

### 输入

```
1 1
0 2 0
```

### 输出

```
0 1 0 
```

# AI分析结果

### 题目内容
# 山脉风景

## 题目描述
小博莱克找到了一幅画有 $n$ 座山峰的画。这 $n$ 座画中的山峰由一条非闭合的折线表示，该折线由 $2n$ 条线段组成。这些线段经过 $2n + 1$ 个点，坐标为 $(1, y_{1})$，$(2, y_{2})$，... ，$(2n + 1, y_{2n + 1})$，第 $i$ 条线段连接点 $(i, y_{i})$ 和点 $(i + 1, y_{i + 1})$ 。对于任何偶数 $i$（$2 \leq i \leq 2n$），满足以下条件：$y_{i - 1} < y_{i}$ 且 $y_{i} > y_{i + 1}$ 。

我们将横坐标为偶数的折点称为山峰顶点。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF218A/96f9e39adc23f097d41530b53dba00529f48c7bd.png) 左边的图展示了初始图片，右边的图展示了博莱克操作后的图片。受影响的山峰用红色标记，$k = 2$ 。博莱克想搞点小恶作剧。他恰好选择了 $k$ 个山峰顶点，擦掉了经过这些顶点的线段，并将每个顶点的高度增加了1（即，他增加了相应点的 $y$ 坐标）。然后他绘制了缺失的线段，得到了一幅新的山峰图片。我们将博莱克新图片中折线经过的点表示为 $(1, r_{1})$，$(2, r_{2})$，... ，$(2n + 1, r_{2n + 1})$ 。

给定博莱克的最终图片，还原初始图片。

## 样例 #1
### 输入
```
3 2
0 5 3 5 1 5 2
```
### 输出
```
0 5 3 4 1 4 2 
```
## 样例 #2
### 输入
```
1 1
0 2 0
```
### 输出
```
0 1 0 
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路基本一致，都是通过遍历偶数下标的点，判断该点减1后是否仍比其左右两边的点大，若满足条件且减的次数未达到 $k$ 次，则将该点减1 。题解们的不同主要体现在代码实现细节，如输入输出方式、数组定义、循环终止条件的写法等。

### 所选的题解
- **作者：Night_sea_64 (5星)**
  - **关键亮点**：思路清晰简洁，代码简短且易读，直接模拟还原过程，用 `cnt` 记录已减的个数，在遍历中实时输出结果。
  - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int a[210];
int main()
{
    int n,k;
    cin>>n>>k;
    n=2*n+1;
    for(int i=1;i<=n;i++)cin>>a[i];
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(i%2==0)
            if(a[i]-1>a[i-1]&&a[i]-1>a[i+1]&&cnt<k)a[i]--,cnt++;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}
```
  - **核心实现思想**：读入数据后，遍历数组，对偶数下标的点进行判断，若符合条件则减1并更新计数，同时遍历过程中输出数组元素。

- **作者：OI_AKed_me (4星)**
  - **关键亮点**：采用快速读入输出模板，代码结构清晰，贪心思想体现明确，即能改则改，改满 $k$ 个就停止。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ss stable_sort
#define inf INT_MAX
#define R read()
#define umap unordered_map
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#pragma GCC opitimize(3)
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
inline void StringRead(string &str){
    char s=getchar();
    while(s==' '||s=='\n'||s=='\r'){
        s=getchar();
    }
    while(s!=' '&&s!='\n'&&s!='\r'){
        str+=s;
        s=getchar();
    }
}
inline int read(){
    int X=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,k,a[505];
int main(){
#ifdef online
	freopen(".in", "r", stdin);
	freopen(".out", "w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	n=R,k=R;
	for(int i=1;i<=2*n+1;i++){
		a[i]=R;
	}
	for(int i=2;i<=2*n;i+=2){
		if(a[i-1]<a[i]-1&&a[i]-1>a[i+1]){
			a[i]--;
			k--;
			if(!k) break;
		}
	}
	for(int i=1;i<=2*n+1;i++){
		write(a[i]);putchar(' ');
	}
//	cout<<endl<<clock();
	return 0;
}
```
  - **核心实现思想**：通过快速读入函数获取数据，遍历偶数下标的点，符合条件则对该点减1并减少 $k$ 的计数，减满 $k$ 次就停止，最后通过快速输出函数输出结果。

- **作者：xiaomuyun (4星)**
  - **关键亮点**：对题意和题目分析详细，代码中使用 `ans` 数组存储结果，逻辑清晰，在遍历中合理利用 `break` 提前结束循环优化效率。
  - **重点代码**：
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
int n,k,a[210],ans[210];
int main(){
	scanf("%d%d",&n,&k);
	n=(n<<1)|1;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) ans[i]=a[i];
	for(int i=2;i<=n;i+=2){
		if(!k) break;
		if(a[i]-1>a[i-1]&&a[i]-1>a[i+1]) --k,--ans[i];
	}
	for(int i=1;i<=n;++i) printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}
```
  - **核心实现思想**：先读入数据并初始化 `ans` 数组为输入数组，遍历偶数下标的点，满足条件则对 `ans` 数组对应元素减1并减少 $k$ 的计数，减满 $k$ 次提前结束循环，最后输出 `ans` 数组。

### 最优关键思路或技巧
直接按照题目描述的还原逻辑进行模拟，利用循环遍历偶数下标的点，通过条件判断确定是否对该点进行减1操作，同时注意用变量记录已操作次数，达到 $k$ 次及时停止，避免无效操作。

### 拓展
此类题目属于简单模拟类型，类似题目通常会给出一些操作规则，要求根据最终状态还原初始状态或进行其他逆向推导。解题时需清晰理解规则，按部就班模拟过程。

### 相似题目推荐
 - [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
 - [P5709 【深基2.例6】字母转换](https://www.luogu.com.cn/problem/P5709)

### 个人心得摘录与总结
 - **作者：xiaomuyun**：强调每个偶数下标的 $i$ 只能减一次1，否则会出错。总结了自己因误解该条件导致提交错误的教训，提醒注意题目细节。 

---
处理用时：61.09秒