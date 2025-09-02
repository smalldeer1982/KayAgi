# [USACO08OCT] Bovine Bones G

## 题目描述

Bessie 喜欢桌游和角色扮演游戏，所以她说服了 Farmer John 驾车送她去爱好商店，在那里她购买了三个用于掷骰子的骰子。这些公平的骰子分别有 $S_1$、$S_2$ 和 $S_3$ 个面（$2 \leq S_1 \leq 20$；$2 \leq S_2 \leq 20$；$2 \leq S_3 \leq 40$），上面分别包含 $1$ 到 $S_1$，$S_2$ 和 $S_3$ 之间的所有整数。Bessie 不断地掷骰子，试图找出哪个三个骰子的点数和出现得最频繁。如果有多个和出现得最频繁，输出其中最小的和。

## 说明/提示

这里是所有可能的结果。

```
1 1 1 -> 3  
1 2 1 -> 4  
2 1 1 -> 4  
2 2 1 -> 5  
3 1 1 -> 5  
3 2 1 -> 6 
1 1 2 -> 4  
1 2 2 -> 5  
2 1 2 -> 5  
2 2 2 -> 6  
3 1 2 -> 6  
3 2 2 -> 7 
1 1 3 -> 5  
1 2 3 -> 6  
2 1 3 -> 6  
2 2 3 -> 7  
3 1 3 -> 7  
3 2 3 -> 8
```

5 和 6 都出现得最频繁（各五次），所以答案是 5。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 2 3 
```

### 输出

```
5 
```

# 题解

## 作者：2011hym (赞：11)

[更好的阅读体验。](https://blog.csdn.net/Hymmeishili/article/details/148459828?sharetype=blogdetail&sharerId=148459828&sharerefer=PC&sharesource=Hymmeishili&spm=1011.2480.3001.8118)

题解区的思路大都是暴力枚举，看完后我突然想起来有一个 $O(1)$ 的做法。

我有一计！

## 题目分析
找出三个骰子所有可能的和中出现次数最高的那个，如果有多个和出现次数相同，则输出字典序**最小**的那个。

## 解决思路
我们可以通过分析骰子面数之间的关系，直接计算最可能出现的和，而不需要枚举所有可能的组合。

三个骰子的和最可能出现在中间区域，具体位置取决于三个骰子面数的相对大小。

## 数学原理

本题解的知识点牵扯到**概率论**，读者自重。

这玩意基于**概率分布**的性质：
- 三个独立均匀分布的**离散随机变量之和**的概率分布呈**近似正态分布**。
- 当最小两个骰子的面数之和不超过最大骰子面数加 $1$ 时，峰值出现在 $1+b+c$。
- 否则峰值出现在更复杂的位置，由给定公式计算。

读者若想了解，可以在 [OI Wiki](https://oiwiki.com/math/probability/basic-conception/) 上搜索。

## 代码实现

这里提供两种做法。

$O(1)$ 做法：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c;
int main() {
    cin>>a>>b>>c;
    // 排序使 a>=b>=c。
    if(a<b)swap(a,b);
    if(b<c)swap(b,c);
    if(a<b)swap(a,b);
    if(b<=a-c+1){
        cout<<1+b+c;
    }else{
        cout<<2+a+(b-a+c-1)/2;
    }
    return 0;
}
```

$O(n^3)$ 做法：

```cpp
#include <bits/stdc++.h>
using namespace std;
int freq[110],ans,cnt,s1,s2,s3;//统计和出现的频率。
int main() {
    cin>>s1>>s2>>s3;
    //枚举所有可能的骰子组。
    for(int i=1;i<=s1;i++){
        for(int j=1;j<=s2;j++){
            for(int k=1;k<=s3;k++){
                int sum=i+j+k;
                freq[sum]++;
            }
        }
    }
    //找出出现频率最高的最小和。
    for(int sum=3;sum<=s1+s2+s3;sum++){
        if(freq[sum]>cnt){
            cnt=freq[sum];
            ans=sum;
        }
    }
    cout<<ans;
    return 0;
}
```

**update**：2025.7.22 修正了两处小错误。

---

## 作者：stardusts (赞：5)

# 简化题意

给定三个数 $s1,s2,s3$，定义 $1 \le a \le s1,1 \le b \le s2,1 \le c \le s3$ ，求所有组合中最频繁的相加之和。

# 思路

由数据范围 $2 \le S_1 \le 20$；$2 \le S_2 \le 20$；$2 \le S_3 \le 40$ 很快变想到暴力枚举，对于相加的结果用一个桶数组累加次数。

# 注意事项

由数据范围得知累加和最多为 $20 + 20 + 40 = 80$，故桶数组 $t$ 开到 $80 +5 = 85$。

桶数组 $t$、最多次数 $num$ 需要初始化为 0 或使其变为全局变量以实现全部初始化为 0。

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;
int s1,s2,s3,t[85],ans,num;
int main(){
    cin>>s1>>s2>>s3;
    for (int u=1;u<=s1;u++)
        for (int v=1;v<=s2;v++)
            for (int w=1;w<=s3;w++)
                if (++t[u+v+w]>num)
                    num=t[u+v+w],ans=u+v+w;
    cout<<ans;
    return 0;
}
```

---

## 作者：dengrunze2608 (赞：5)

简单的枚举题
## 题目内容
Bessie买了三个骰子分别有 $S_1$、$S_2$ 和 $S_3$ 个面（$2 \le S_1 \le 20,2 \le S_2 \le 20,2 \le S_3 \le 40$）。她不断掷骰子，要找出三个骰子的和出现得最频繁的那个（如果有多个和出现的频率相同，则输出其中最小的和）。
## 分析
枚举三个骰子所有可能的组合的和，统计每个和出现的次数。然后找出出现次数最多的和，如果有多个一样的就选最小的那个。这里我用了一个 $he$ 数组记录每个和出现的次数，最后遍历 $he$ 数组，打擂找到出现次数最多的和。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int s1,s2,s3,he[16005],maxn=-INT_MAX;
int maxx=-INT_MAX,h;
int main(){
	cin>>s1>>s2>>s3;
	for(int i=1;i<=s1;i++){
		for(int j=1;j<=s2;j++){
			for(int k=1;k<=s3;k++){//标记所有和出现次数。 
				he[i+j+k]++;
				maxn=max(maxn,i+k+j);
			}
		}
	}
	
	for(int i=1;i<=maxn;i++){//遍历所有可能的和，找到出现次数最多的最小的和。 
		if(he[i]>maxx){
			maxx=he[i];
			h=i;//用 h 记录最小的和。
		}
	}
	cout<<h;
	return 0;
}
```

---

## 作者：The_Chariot (赞：3)

怎么没有题解？水一发。

先让我们想一想骰子的性质：每个面朝上的概率都相等。如果你会小学数学，那么这道题你只需要求出三个骰子掷出数字的和的方案数。

但是问题来了，怎么记录这些方案数呢？

我们将会使用一个在 c++ 中及其常用的数据结构：数组来解决。

以下是数组定义的代码：
```cpp
int a[N];//N代表你的数组大小，N越大数组能存储的东西越多
```
数组可以在你想要的位置存储一个数。

所以，我们就有办法记录方案数了。

这时候就可以使用我们大名鼎鼎的枚举了！

用 for 循环嵌套三次枚举每个骰子朝上的数，再全部加起来得到总和 $s$，便在 $a$ 数组对应的 $s$ 位置加 1。

最后再循环一遍 $a$ 数组，找到方案数最大的那个位置，输出它，本题就顺利通过了！

数组在信息学竞赛中用处极大，希望你能掌握它的用法，在这条路上勇往直前。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int max_f,ans;
int main(){
	int s1,s2,s3;
	cin >> s1 >> s2 >> s3 ;
	for(int i = 1;i <= s1;i ++){
		for(int j = 1;j <= s2;j ++){
			for(int k = 1;k <= s3;k ++){
				int s = i + j + k;
				a[s] = a[s] + 1;
			}
		}
	}
	for(int s = 1;s <= s1 + s2 + s3; s++){
		if(a[s] > max_f){
			ans = s;
			max_f = a[s];
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ZYX0716 (赞：2)

[P2911](https://www.luogu.com.cn/problem/P2911)

## 思路：

由题面得知，本题要求**三个数的和组成的数列**中的**最小众数**。

往下看数据范围，因为 $2 \le S1 \le 20$，$2 \le S2 \le 20$ 且 $2 \le S3 \le 40$，而 $20 \times 20 \times 40 = 16000$，这意味着**暴力**不会超时。 

## CODE:

明确思路后代码其实很简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,x[100],maxn,ans=INT_MAX;
int main(){
	//此处可自行添加快读等提速代码。
	cin>>a>>b>>c;
	for(int i=1;i<=a;i++){//依次枚举。
		for(int j=1;j<=b;j++){
			for(int k=1;k<=c;k++){
				int s=i+j+k;//求和。
				x[s]++;//和为s的组合出现次数。
				if(x[s]==maxn){//最小的众数。
					ans=min(ans,s);
				}if(x[s]>maxn){//次数最大。
					maxn=x[s];
					ans=s;
				}
			}
		}
	}
	cout<<ans;//输出出现次数最多的最小的数。
	return 0;//好习惯。
}
```
有疑问记得私信哦！

---

## 作者：_WorldHello_ (赞：1)

2025.7.20 update:修正语误
## 题目大意
给定 $3$ 个不同的筛子，分别有 $s_{1},s_{2},s_{3}$ 个面，求出现次数最高的三个筛子上的数之和的最小值。

## 解决思路
定义 $p$ 数组记录每一次可能筛出的数之和的次数，最后记录出现次数最高的三个筛子上的数之和的最小值。

## AC代码(含注释)
```cpp
#include<bits/stdc++.h>
using namespace std;
int s1,s2,s3,p[85]; //p数组范围:20+20+40
int maxx,maxxx;
int main(){
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //ios::sync_with_stdio(0);
    //cin.tie(0);cout.tie(0);
    cin>>s1>>s2>>s3;//输入
    for(int i=1;i<=s1;i++)
        for(int j=1;j<=s2;j++)
            for(int k=1;k<=s3;k++)
                p[i+j+k]++;
    //记录筛出的点数
    for(int i=3;i<=s1+s2+s3;i++)
        if(p[i]>maxx)
            maxx=p[i],maxxx=i;
    cout<<maxxx;
    //找出出现频率最多的点数并输出最大值
	return 0;
}

```

---

## 作者：Clare613 (赞：0)

## 思路：
USACO 远古题，很简单，只要把每一种情况找出来，算一下和并记录，找到次数最多的输出即可。对于萌新们，只要用三重循环来遍历所有情况即可，就没了。\
三重循环就是分别从 $1$ 到 $a$、 $1$ 到 $b$、$1$ 到 $c$，这样的原因是为了遍历到所有的情况。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int q[65];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int a,b,c;
	cin>>a>>b>>c;
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			for(int k=1;k<=c;k++){
				q[i+j+k]++;
			}
		}
	}
	int maxn=0,id=0;
	for(int i=1;i<=a+b+c;i++){
		if(maxn<q[i]){
			maxn=q[i];
			id=i;
		}
	}
	cout<<id;
	return 0;
}
```

---

