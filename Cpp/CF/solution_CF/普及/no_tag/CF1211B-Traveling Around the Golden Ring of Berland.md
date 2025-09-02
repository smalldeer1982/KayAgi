# Traveling Around the Golden Ring of Berland

## 题目描述

一位博主Polycarp想游览柏林的著名景点The Golden Ring.

The Golden Ring由n个城市组成为环状，城市编号由1到n。（注意：和第n个城市相连的是第一个城市和第n-1个城市）已知Polycarp想在每个城市拍几张自拍，Polycarp从第一个城市开始他的旅程，并且循环旅行，也就是说他从1城市到n城市后下一个访问的城市仍然是1城市。他每次访问一个城市至多拍一张自拍，而且循环旅行时经过的城市都要访问（无论拍不拍自拍）。

现在要求求出Polycarp的城市访问数。

## 样例 #1

### 输入

```
3
1 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 0 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5
0 3 1 3 2
```

### 输出

```
14
```

## 样例 #4

### 输入

```
5
1000000000 1000000000 1000000000 1000000000 0
```

### 输出

```
4999999999
```

# 题解

## 作者：夙愿扬 (赞：5)

# CF1211B

这个场次的比赛是Kotlin语言（~~这语言貌似是改掉了Java的痛点~~）的专场，不能用其他语言提交，交了的话。。

![](https://cdn.luogu.com.cn/upload/image_hosting/6mfjkxhl.png)

~~（真行）~~


------------

还是大概讲一下思路吧（用c++实现）

把数据读入以后就扫一遍最大值，保存一下节点（不过要注意如果当前扫到的与最大值相等，一定要更新，因为我们需要最后的最大值）

最后输出（ 最大值 - 1 ）* n + 最大值下标；

## 对了一定要开 **long long**
### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main ()//一定记得要开long long
{
    long long n,a[1000001],maxn=0,maxm;//maxn存最大值，maxm存最大值下标
    scanf("%lld",&n);
    for(long long i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);//读入
        if(a[i]>=maxn)//跟着把数组扫一遍
        {
            maxn=a[i];
            maxm=i;
        }
    }
    printf("%lld",(a[maxm]-1)*n+maxm);//公式直接输出
    return 0;
}
```
###### The End——2019/9/24 18:24

---

## 作者：ICU152_lowa_IS8 (赞：1)

本题 C++ 似乎提交不了……

其实本题非常简单。


------------
首先我们看到题目中的**每次访问一个城市至多拍一张自拍。**

那么就说明，如果需要自拍数量 $>1$，那么就需要通过循环旅行来满足需要自拍数量。

而很明显，需要循环的次数为所有需要自拍数量中的最靠后的最大值减一（为什么要减一后面会讲到）。

为什么要最靠后的最大值？稍微想一想，很容易得出来结论，我就不说了。

说的可能不是很明白，举个例子：

输入如下数据：

```
3
2 3 2
```

在这种情况下，可以看到最后最大值为 $3$，需要循环旅行 $3-1$ 次，即 $2$ 次。



------------

好，现在我们来说说为什么循环次数要减一：

还是使用上边的那个数据：

```
3
2 3 2
```

如果循环次数不减一，那么需要循环 $3$ 次，一共走了 $3\times3=9$ 次。但是显而易见，只需要走 $8$ 次就行了。

为什么呢？

很明显，当走到下标为 $2$ 的位置（下标从 $1$ 开始）的时候，已经可以停止了，然而循环 $3$ 次会让咱们那位 Polycarp 继续周游他的城市，从而多出几次不必要的访问。

概括一下：**如果循环次数不减一，当最后最大值下标不为 $n$ 的时候，由最后最大值下标 $+1$，最后最大值下标 $+2$，$\cdots$，一直到下标为 $n$ 的位置，都会多出一次不必要的循环。**

------------

当然了，循环次数减一的时候，肯定是有一些和最后最大值相等的需要自拍数目没有满足。

很明显，此时 Polycarp 的位置是 $1$ 城市，只需要走到最后最大值的位置，也就是之前循环旅行加上最后最大值的下标就可以了。


------------


至于代码，因为我不会 C++ 以外的语言，所以本题解只能提供思路。

---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1211B)

### 分析
因为每个景点必须拍够足够的照片，所以只需要找的最后一个拍照数量最大的景点，然后轮回景点次数为（最大照片数 $-1$），最后再加上该景点位置即可。

输出就相当于：最后输出（最大值 $-1$）$\times$ 景点个数 $+$ 最大值下标（一定是最后一个）。


------------

### 解释

------------


1. 为什么一定还要找到最后一个拍照数量最大的景点？

答：要跑到那个点为止才算拍照拍完。

------------


2. 轮回数为什么 $-1$？

答：因为最后一个点下标不一定是在最后。

Hack 样例：

```cpp
5
2 3 2 3 2
```


------------


3. 为什么提交会 UKE?

答：因为本场比赛 c++ 无法成功运行（其它题解说的）。

------------


4. 本题是否需要开 long long？

答：就数据范围来，需要！

------------



#### 注意：本代码思路对的，样例也能全过，但会 UKE！


------------

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b[100005];
long long Max;//最大值
long long point;//最大值下标
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>b[i];
		if(Max<=b[i]){//注意：是<=，因为一定要是一个最后的最大景点
			Max=b[i];//轮回次数
			point=i;//记录最大点位置
		}
	}
	cout<<(b[point]-1)*a+point;//最后输出（ 最大值 - 1 ）* n + 最大值下标；
	return 0;
}

```

---

## 作者：2021zjhs005 (赞：0)

温馨提示：此题不能用 `C++` 提交，因为该场比赛都是用 `kotlin` 语言，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/3ljo83ex.png)

否则，你就会：

![](https://cdn.luogu.com.cn/upload/image_hosting/7u0lic9n.png)



Despriction
------------

有 $n$ 个城市，`Polycarp` 想要在第 $i$ 个城市拍 $a_i$ 张照片（保证至少有一个 $a_i$ 严格大于 $0$）。

每次旅游的顺序是：$1\rightarrow 2\rightarrow 3\rightarrow\cdots\rightarrow n\rightarrow 1\rightarrow\cdots$，也就是**环形**旅游。每次旅游的城市只能拍 $1$ 张照（当然你不想拍也可以不拍）。

问至少旅游了多少个城市？

Solution
------------

如果说要结束旅游，那么第 $i$ 个城市拍的照片都必须等于 $a_i$（等你拍够了可以不拍，所以可以等于）。

那么最后游玩的城市一定是 $\max_{i=1}^n a_i$ 所对应的城市下标 $i$。

设 $maxn=max_{i=1}^n a_i$，考虑到 $maxn$ 可能有多个，那么最后游玩的城市一定是最后面的那个 $maxn$ 所对应的城市小标。

这是一共绕了都市 $\frac{(maxn-1)}{1}=maxn-1$ 圈（这是第 $maxn$ 圈，结束），令 $pos$ 为这个 $maxn$ 的下标，则总共游玩了 $(maxn-1)\times n+pos$ 个城市。

Code
------------

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define stg string
#define vct vector
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

ll n,maxn=INT_MIN,pos;

int main(){
  n=read();
  rep(i,1,n){
    ll x=read();
    if(x>=maxn){//保留最后一个 maxn 所对应的下标，用 >=maxn 解决，而不是 >maxn。
      maxn=x;
      pos=i;//比最大值，并且记录位置。
    }
  }
  pr("%lld\n",(maxn-1ll)*n+pos);
  return 0;
}
```



------------
当然，还要感谢 @[QWQ_123](https://www.luogu.com.cn/user/740328) 提供 `kotlin` 代码，让本蒟蒻学习了一番。

`kotlin` 语言和 `java` 语言很像，你可以把它理解为 `java`（不过又一点点不一样）。

```java
import java.util.Scanner//导入 java.util 包下的 Scanner 类，导入后才能使用它。

fun main(args: Array<String>) {//可以把它理解为 C++ 里的 int main()。fun，形象地理解为和 C++ 里的 auto 一样。

    val reader = Scanner(System.`in`)//reader 对象调用下列方法(函数),读取用户在命令行输入的各种数据类型。
    
    var x:Long = reader.nextLong()//x:Long 中，: 后面的是变量类型。这个形象地可以理解为读入。
    var n:Long = x//赋值。
    var maxn:Long = 0//赋值。
    var id:Long = 0
    var i:Long = 0
    while (x > 0) {//循环。
        ++i
        var t:Long = reader.nextLong()//读入。
        
        if (t >= maxn) {//打擂台。
            maxn = t//更新擂台主。
            id = i//记录位置。
        }
        --x
    }//这其实就是个普通的 while() 循环。
    
    println((maxn - 1) * n + id)//输出是 println()，也就是 print + line 缩写为 println。
    
//如果你想输出空格，那么可以： System.out.print("***"); 记得在 *** 里面加上空格。
}
```

在此依旧感谢 @[QWQ_123](https://www.luogu.com.cn/user/740328)。

![](https://cdn.luogu.com.cn/upload/image_hosting/6h15e2eh.png)

---

## 作者：Stars_visitor_tyw (赞：0)

## CF1211B Traveling Around the Golden Ring of Berland 题解
### 分析
这题是 Kotlin 语言专场的题，用其他语言交会 UKE……

讲一下思路。城市访问次数主要取决于要拍的自拍数最大的城市，设这个自拍数最大的城市为 $maxi$，在 $maxi$ 拍完第 $a_{maxi} -1$ 张照片前，所有城市都得跑 $a_{maxi} -1$ 遍，加起来就是 $(a_{maxi}-1) \times n$ 次。$maxi$ 的最后一次自拍只需访问 $maxi$ 个城市即可拍完，总次数为 $(a_{maxi}-1) \times n +maxi$。

注意：若有多个 $a_i$ 同时为最大值，取编号最大的那个。

### 代码（C++）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node
{
    int v, id;
}a[200005];
bool cmp(node x, node t)
{
    if(x.v==t.v)
    {
        return x.id>t.id;
    }
    return x.v>t.v;
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].v;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    int maxi=a[1].id;
    cout<<(a[1].v-1)*n+maxi;
    return 0;
}
```

---

