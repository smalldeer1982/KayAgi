# 题目信息

# Karen and Coffee

## 题目描述

To stay woke and attentive during classes, Karen needs some coffee!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF816B/84ca24fa194ecce1cb9c3e825b543dfb7809c444.png)Karen, a coffee aficionado, wants to know the optimal temperature for brewing the perfect cup of coffee. Indeed, she has spent some time reading several recipe books, including the universally acclaimed "The Art of the Covfefe".

She knows $ n $ coffee recipes. The $ i $ -th recipe suggests that coffee should be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive, to achieve the optimal taste.

Karen thinks that a temperature is admissible if at least $ k $ recipes recommend it.

Karen has a rather fickle mind, and so she asks $ q $ questions. In each question, given that she only wants to prepare coffee with a temperature between $ a $ and $ b $ , inclusive, can you tell her how many admissible integer temperatures fall within the range?

## 说明/提示

In the first test case, Karen knows $ 3 $ recipes.

1. The first one recommends brewing the coffee between $ 91 $ and $ 94 $ degrees, inclusive.
2. The second one recommends brewing the coffee between $ 92 $ and $ 97 $ degrees, inclusive.
3. The third one recommends brewing the coffee between $ 97 $ and $ 99 $ degrees, inclusive.

A temperature is admissible if at least $ 2 $ recipes recommend it.

She asks $ 4 $ questions.

In her first question, she wants to know the number of admissible integer temperatures between $ 92 $ and $ 94 $ degrees, inclusive. There are $ 3 $ : $ 92 $ , $ 93 $ and $ 94 $ degrees are all admissible.

In her second question, she wants to know the number of admissible integer temperatures between $ 93 $ and $ 97 $ degrees, inclusive. There are $ 3 $ : $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In her third question, she wants to know the number of admissible integer temperatures between $ 95 $ and $ 96 $ degrees, inclusive. There are none.

In her final question, she wants to know the number of admissible integer temperatures between $ 90 $ and $ 100 $ degrees, inclusive. There are $ 4 $ : $ 92 $ , $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In the second test case, Karen knows $ 2 $ recipes.

1. The first one, "wikiHow to make Cold Brew Coffee", recommends brewing the coffee at exactly $ 1 $ degree.
2. The second one, "What good is coffee that isn't brewed at at least $ 36.3306 $ times the temperature of the surface of the sun?", recommends brewing the coffee at exactly $ 200000 $ degrees.

A temperature is admissible if at least $ 1 $ recipe recommends it.

In her first and only question, she wants to know the number of admissible integer temperatures that are actually reasonable. There are none.

## 样例 #1

### 输入

```
3 2 4
91 94
92 97
97 99
92 94
93 97
95 96
90 100
```

### 输出

```
3
3
0
4
```

## 样例 #2

### 输入

```
2 1 1
1 1
200000 200000
90 100
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

# Karen和咖啡

## 题目描述

为了在课堂上保持清醒和专注，Karen需要一些咖啡！

Karen是一位咖啡爱好者，她想知道冲泡完美咖啡的最佳温度。她花了一些时间阅读了几本食谱，包括广受好评的《The Art of the Covfefe》。

她知道$n$个咖啡食谱。第$i$个食谱建议咖啡的冲泡温度在$l_{i}$到$r_{i}$度之间（包括$l_{i}$和$r_{i}$），以达到最佳口感。

Karen认为，如果一个温度被至少$k$个食谱推荐，那么这个温度是可接受的。

Karen的思维比较善变，所以她提出了$q$个问题。在每个问题中，给定她只想在$a$到$b$度之间（包括$a$和$b$）冲泡咖啡，你能告诉她有多少个可接受的整数温度落在这个范围内吗？

## 说明/提示

在第一个测试用例中，Karen知道$3$个食谱。

1. 第一个食谱建议在$91$到$94$度之间冲泡咖啡。
2. 第二个食谱建议在$92$到$97$度之间冲泡咖啡。
3. 第三个食谱建议在$97$到$99$度之间冲泡咖啡。

一个温度如果被至少$2$个食谱推荐，那么它是可接受的。

她提出了$4$个问题。

在她的第一个问题中，她想知道在$92$到$94$度之间有多少个可接受的整数温度。有$3$个：$92$、$93$和$94$度都是可接受的。

在她的第二个问题中，她想知道在$93$到$97$度之间有多少个可接受的整数温度。有$3$个：$93$、$94$和$97$度都是可接受的。

在她的第三个问题中，她想知道在$95$到$96$度之间有多少个可接受的整数温度。没有。

在她的最后一个问题中，她想知道在$90$到$100$度之间有多少个可接受的整数温度。有$4$个：$92$、$93$、$94$和$97$度都是可接受的。

在第二个测试用例中，Karen知道$2$个食谱。

1. 第一个食谱“wikiHow to make Cold Brew Coffee”建议在$1$度冲泡咖啡。
2. 第二个食谱“What good is coffee that isn't brewed at at least $36.3306$ times the temperature of the surface of the sun?”建议在$200000$度冲泡咖啡。

一个温度如果被至少$1$个食谱推荐，那么它是可接受的。

在她的第一个也是唯一一个问题中，她想知道在$90$到$100$度之间有多少个可接受的整数温度。没有。

## 样例 #1

### 输入

```
3 2 4
91 94
92 97
97 99
92 94
93 97
95 96
90 100
```

### 输出

```
3
3
0
4
```

## 样例 #2

### 输入

```
2 1 1
1 1
200000 200000
90 100
```

### 输出

```
0
```

### 题解分析与结论

#### 总体思路
1. **差分数组**：用于高效地记录每个温度被推荐的次数。通过在每个区间的起点加1，在终点+1的位置减1，最后通过累加得到每个温度被推荐的总次数。
2. **前缀和**：用于快速查询某个温度区间内有多少个温度被推荐次数大于等于$k$。通过预处理，可以在$O(1)$时间内回答每个查询。

#### 难点对比
- **差分数组的使用**：差分数组是解决区间更新问题的常用技巧，能够将区间更新的时间复杂度从$O(n)$降低到$O(1)$。
- **前缀和的优化**：前缀和的使用使得查询操作可以在$O(1)$时间内完成，极大地提高了查询效率。

#### 最优关键思路
- **差分数组**：通过差分数组高效处理区间更新问题。
- **前缀和**：通过前缀和快速回答区间查询问题。

### 精选题解

#### 1. 作者：智子·起源 (赞：45)
- **星级**：★★★★★
- **关键亮点**：清晰地解释了差分数组和前缀和的使用，代码简洁高效。
- **代码实现**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,k,f[200000+5],ff[200000+5],fff[200000+5],a,b;
int main()
{
  scanf("%d%d%d",&n,&k,&m);
  for(int i=0;i<n;i++)
  {
    scanf("%d%d",&a,&b);
    ff[a]++,ff[b+1]--;
  }
  for(int i=1;i<=200000;i++)
  {
    f[i]=f[i-1]+ff[i];
    if(f[i]>=k)fff[i]=fff[i-1]+1;
      else fff[i]=fff[i-1];
  }
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&a,&b);
    printf("%d\n",fff[b]-fff[a-1]);
  }
  return 0;
}
```

#### 2. 作者：AISakura (赞：12)
- **星级**：★★★★
- **关键亮点**：通过结构体保存区间边界，使用计数器统计每个温度被推荐的次数，思路清晰。
- **代码实现**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int s[200001],te[200001];
struct qj{
	int l,r;
}t[200001];
int main(){
	int n,k,q,a,b,tot=0;
	scanf("%d%d%d",&n,&k,&q);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		t[a].l++;   t[b].r++; 
	}
	for(int i=1;i<=200001;i++){
		tot+=t[i].l;   tot-=t[i-1].r; 	 
		te[i]=tot;          
	}
	for(int i=1;i<=200001;i++)             
		if(te[i]>=k)
			te[i]=1;
		else
			te[i]=0;
	for(int i=1;i<=200001;i++)             
		s[i]=te[i]+s[i-1];
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",(s[b]-s[a]+te[a]));
	}
	return 0;
}
```

#### 3. 作者：Khassar (赞：4)
- **星级**：★★★★
- **关键亮点**：简洁地使用差分和前缀和，代码清晰易懂。
- **代码实现**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#define ll long long
#define R register
#define IL inline
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define MES(a,b) memset((a),(b),sizeof((a)))
#define MEC(a,b) memcpy((a),(b),sizeof((b)))
#define D double
using namespace std;
const int N=200005;
int n,k,q,a[N],b,c[N],up;
IL int read() {
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
IL void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
signed main()
{
	n=read();k=read();q=read();
	Rf(i,1,n) {
		R int l=read(),r=read();
		a[l]++;a[r+1]--;
		up=max(up,r+1);
	}
	up=N-3;
	Rf(i,1,up) {
		b+=a[i];
		if(b>=k) c[i]=1;
		c[i]+=c[i-1];
	}
	Rf(i,1,q) {
		R int l=read(),r=read();
		write(c[r]-c[l-1]);
		putchar('\n');
	}
    return 0;
}
```

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得总结
- **差分数组的使用**：差分数组在处理区间更新问题时非常高效，能够将时间复杂度从$O(n)$降低到$O(1)$。
- **前缀和的优化**：前缀和的使用使得查询操作可以在$O(1)$时间内完成，极大地提高了查询效率。
- **代码简洁性**：代码的简洁性和可读性对于理解和调试非常重要，尤其是在竞赛中。

---
处理用时：71.94秒