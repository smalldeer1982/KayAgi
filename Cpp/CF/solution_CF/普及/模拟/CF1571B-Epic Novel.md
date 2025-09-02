# Epic Novel

## 题目描述

Alex has bought a new novel that was published in $ n $ volumes. He has read these volumes one by one, and each volume has taken him several (maybe one) full days to read. So, on the first day, he was reading the first volume, and on each of the following days, he was reading either the same volume he had been reading on the previous day, or the next volume.

Let $ v_i $ be the number of the volume Alex was reading on the $ i $ -th day. Here are some examples:

- one of the possible situations is $ v_1 = 1 $ , $ v_2 = 1 $ , $ v_3 = 2 $ , $ v_4 = 3 $ , $ v_5 = 3 $ — this situation means that Alex has spent two days ( $ 1 $ -st and $ 2 $ -nd) on the first volume, one day ( $ 3 $ -rd) on the second volume, and two days ( $ 4 $ -th and $ 5 $ -th) on the third volume;
- a situation $ v_1 = 2 $ , $ v_2 = 2 $ , $ v_3 = 3 $ is impossible, since Alex started with the first volume (so $ v_1 $ cannot be anything but $ 1 $ );
- a situation $ v_1 = 1 $ , $ v_2 = 2 $ , $ v_3 = 3 $ , $ v_4 = 1 $ is impossible, since Alex won't return to the first volume after reading the third one;
- a situation $ v_1 = 1 $ , $ v_2 = 3 $ is impossible, since Alex doesn't skip volumes.

You know that Alex was reading the volume $ v_a $ on the day $ a $ , and the volume $ v_c $ on the day $ c $ . Now you want to guess which volume was he reading on the day $ b $ , which is between the days $ a $ and $ c $ (so $ a < b < c $ ). There may be some ambiguity, so you want to make any valid guess (i. e. choose some volume number $ v_b $ so it's possible that Alex was reading volume $ v_a $ on day $ a $ , volume $ v_b $ on day $ b $ , and volume $ v_c $ on day $ c $ ).

## 说明/提示

In the first test case, since Alex was reading volume $ 1 $ both at day $ 1 $ and at day $ 100 $ then he was reading volume $ 1 $ at any day between them.

In the second test case, Alex could read any volume from $ 1 $ to $ 4 $ at day $ 16 $ . For example, he could read volume $ 1 $ from day $ 1 $ to day $ 15 $ , volume $ 2 $ at days $ 16 $ and $ 17 $ , volume $ 3 $ at day $ 18 $ and volume $ 4 $ at days $ 19 $ and $ 20 $ .

In the third test case, there is only one possible situation: Alex read one volume per day, so at day $ 42 $ he read volume $ 42 $ .

## 样例 #1

### 输入

```
4
1
1 1
100 1
99
4
10 1
20 4
16
100
1 1
100 100
42
100
1 1
100 2
99```

### 输出

```
1
2
42
1```

# 题解

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1571B)

### 思路

本题需要根据 Alex 读书开始的时间确定答案，需要分类讨论：

- 若 $v_c-v_c>b-a$，则 Alex 在第 $a$ 天开始读小说，再读第 $v_c+b-a$ 章。

- 否则说明 Alex 一直在读第 $v_c$ 章。

**CODE**

```c
#include<stdio.h>
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
int main(){
	int t=read();
	while(t--){
		int n=read(),a=read(),va=read(),c=read(),vc=read(),b=read();
		printf("%d\n",(b-a>vc-va)?(va+b-a):vc);
	}
	return 0;
}
```

---

## 作者：Arefa (赞：3)

## 题目思路

由于本题答案有多种时可以任意数出一种，那么可以考虑极端情况。

假设 Alex 从第 a 天开始，每天读一章，若果读到了第 c 天读的章节，就每天重复读此章。这样可以确保这个方案是合法的。

于是就变成当 $b-a>Vc-Va$ 时，第 b 天读第 $Vc$ 章，否则读第 $Va+(b-a)$ 章。

## kotlin代码

```
import java.util.Scanner
fun main() {
    val read = Scanner(System.`in`)
    var n = read.nextInt()
    while(n>0){
        n--
        var z=read.nextInt()
        var d1=read.nextInt()
        var v1=read.nextInt()
        var d2=read.nextInt()
        var v2=read.nextInt()
        var b=read.nextInt()
        if(b-d1>=v2-v1) println(v2)
        else println(v1+b-d1)
    }
}
```


---

## 作者：nightwatch.ryan (赞：3)

### 题意
Alex 买了一本 $n$ 章的小说，为了保证内容的连续性，他不会跳章看，也不会回头看，每一章可能会重复读，但一天不会读多页。第一天他读第 $1$ 页。已知 Alex 在第 $a$ 天读第 $v_a$ 章，第 $c$ 天读第 $v_c$ 章，请判断在第 $b\ (a < b < c)$ 天他在读第几章，输出任意可能解。
### 思路
- 如果 $b-a \ge v_c-v_a$（因为 $v_c$ 是 Alex 在第 $c$ 天阅读的，那么第 $c$ 天和第 $c$ 天以前 Alex 都读第 $v_c$ 章）输出 $v_c$。
- 如果 $b-a \lt v_c-v_a$（因为 Alex 会在第 $a$ 天开始顺序阅读小说的章节，故 Alex 在读第 $v_a+(b-a)$ 页）输出 $v_a+(b-a)$。

### 代码
```cpp
#include<iostream>
int t,n,a,va,c,vc,b,vb;
int main(){
	std::cin>>t;
	for(;t;t--){
		std::cin>>n>>a>>va>>c>>vc>>b;
		if(b-a>=vc-va) std::cout<<vc;
		else std::cout<<va+(b-a); 
		std::cout<<'\n';
	}
}
```



---

## 作者：cute_overmind (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1571B)
### 题目大意
Alex 买了一本章节为 $n$ 的小说，为了保证内容的连续性，他不会跳章看，也不会回头看，每一章可能会读一天或多于一天，但一天不会读多页。第一天他读第 $1$ 章。
### 题目分析
我们可以分类讨论来进行判读答案是否合法。

- 如果 $v_c - v_a > b - a$，那么证明他在第 $a$ 天开始阅读这本小说。所以他现在在读第 $v_c + b - a$ 章。
- 如果 $v_c - v_a \le b - a$，那么证明他在第 $c$ 天以及第 $c$ 天之前都是在读第 $v_c$ 章。

所以代码易得。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t , n , a , va , c , vc , b;
void solve(){
	cin >> n >> a >> va >> c >> vc >> b;
	if(b - a > vc - va) cout << va + b - a << '\n';
	else cout << vc << '\n'; 
}
int main()
{
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 题意简述

由于翻译较为完整，不再赘述。

## 开始解题！

注意到对于所有 $2 \le i \le n$，有 $v_i \ge v_{i - 1}$，然后就很可做了。

我们使用分类讨论来完成此题。

- 若 $v_c \ge v_a + b - a$，即当 $v_c$ 大于等于第 $b$ 最多可读的章数（$v_a + b - a$），我们直接输出 $v_a + b - a$ 即可。
- 反之，则一定存在一种方案，使得在第 $b$ 天前已经看到了 $v_c$ 章，输出 $v_c$ 即可。

不过可惜是个 Kotlin 题，但是放一下 C++ code : 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    ll T; cin >> T;
    
    while (T--) {
        ll n, a, b, c, va, vc; 
        
        cin >> n >> a >> va >> c >> vc >> b;
        
        if (vc >= va + b - a) {
            cout << (va + b - a) << endl;
        } else {
            cout << vc << endl;
        }
    }
    
    return 0;
}
```

这个题是比较基础的，如果有写 Kotlin 的选手也可以在此基础上写出 Kotlin 语言的代码。

做完了。

---

## 作者：focus_aurora (赞：0)

## 思路

分类讨论。

- 如果 $v_c-v_a > b-a$，证明他在第 $a$ 天开始阅读这本小说，现在正在阅读第 $v_c-b+a$ 章。

- 否则证明他一直在读第 $v_c$ 章。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,a,va,c,vc,b;
		scanf("%d%d%d%d%d%d",&n,&a,&va,&c,&vc,&b);
		if(vc-va>b-a){
			printf("%d\n",va+b-a);
		}
		else{
			printf("%d\n",vc);
		}
	}
    return 0;
}
```

---

## 作者：_Michael0727_ (赞：0)

# 题解：CF1571B Epic Novel

[文章食用效果更佳](https://www.luogu.com.cn/article/7hhgvxt5)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF1571B)

### 题意

亚历克斯买了一本 $n$ 章的小说。为了保证内容的连续性，他不会跳章，也不会回看；他可以每章读一天或更长时间，但每天读的页数不会超过一页。第一天，他阅读第 $1$ 章。

已知亚历克斯在 $a$ 日阅读 $v_a$ 章，在 $c$ 日阅读 $v_c$ 章，请确定他在 $b(a < b < c)$ 日阅读哪一章，并输出任何可能的解。

---

## 思路

题目说输出任意可能，所以可以进行枚举，通过分类讨论判断答案是否合法。

**如果 $b - a > v_c - v_a$ 时，那么他在第 $a$ 天开始阅读，现在在读第 $v_c + b - a$ 章，否则他在第 $c$ 天及以前都在读第 $v_c$ 章。**

---

**AC 代码**

比较简单，不贴代码。

---

## 作者：GeYang (赞：0)

# 题意

某人有一本 $n$ 章的小说，他从头开始读，不会跳着读，也不会往回读。

已知他第 $a$ 天读到第 $v_a$ 章，第 $c$ 天读到第 $v_c$ 章，求第 $b$ 天可能读到的章节。

# 思路

如果 $b$ 和 $a$ 的差大于或等于 $v_c$ 和 $v_a$ 的差，那么说明他在第 $c$ 天及之前都在读第 $v_c$ 章。输出 $v_c$ 即可。

如果 $b$ 和 $a$ 的小于 $v_c$ 和 $v_a$ 的差，那么说明他在第 $a$ 天开始读小说，到了第 $b$ 天就在读第 $b-a+v_a$ 章。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	int n,a,va,c,vc,b,ans;
	cin>>n>>a>>va>>c>>vc>>b;
	if(vc-va>b-a) cout<<b-a+va<<endl;
	else cout<<vc<<endl;
} 
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：_Starlit__Sky_ (赞：0)

# 洛谷 CF1571B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF436B)

## 题目算法

模拟

## 题目思路

设第 $b$ 天读的章数为 $v_b$。

由于我们仅需输出任意一个 $v_b$，则考虑从 $v_a$ 开始枚举每个 $v_b$：

- 如果 $v_b < v_c$ 则 $v_b$ 自增。（由于 `Alex` 看的章节小于 $v_c$，则他可以继续看下去）。

- 如果 $v_b=v_c$ 则 直接输出 $v_c$。（由于 `Alex` 已经看到 $v_c$，则他不可以再看下去了，之后的天数都得看 $v_c$，因为第 $c$ 点看的是 $v_c$，如果现在看的章数比 $v_c$ 多，则到第 $c$ 天再看 $v_c$ 属于违法行为，因为他回头看了）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,t,a,va,b,vb,c,vc; 

int main()
{
	scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		scanf("%d%d",&a,&va);
		scanf("%d%d",&c,&vc);
		scanf("%d",&b);
		vb = va; // 从 va 开始 
		for (int i = a ; i < c ; i++){
			if (vb < vc) vb++;
			else{
				cout << vc << endl;
				goto next;
			}
		}
		cout << vb << endl;
		next:;
	} 
	return 0;
}

```

~~点个赞再走吧~~ $awa$

---

## 作者：qusia_MC (赞：0)

~~这是我见过最水的黄题~~直接开始，不多废话。
## 题意
一个人在读小说，不能跳章、反着看，求第 $b$ 天他在看第几页。
## 思路
题目说“输出任意可能解”这就简单了。我们只需要判断他可能读哪一章就OK了。

既然输出一种可能就行了，所以我们尽量要让这个结果好算一些。我们就让他每天读一章（由于不能跳章读，最后的第  $vc$ 章直接让剩下的几天全部读这一章就行了）。

这种情况我们就要分类讨论。第一种情况就是等着到第 $b$ 天的时候已经读到第 $vc$ 章了，也就是：

$vc-va$（中间的章节数）$\le b-a$（从 $a$ 到 $b$ 的天数）这样的话，直接输出 $vc$ 就可以了。剩下的 $c-b$ 天直接全都读 $vc$ 章就好了~~希望这章精彩，不然他会看腻的~~。

第二种情况，就是到第 $b$ 天的时候还没读到第 $vc$ 章。这样的话，输出 $va+(b-a)$ 用开始读的章数加上又往后读的章数。

代码也是非常的简单：

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,a,b,va,vc,c;//定义，没什么好说的
    cin>>t;
    while(t--)//循环t次，记住不能用while(--t)
    {
        cin>>n>>a>>va>>c>>vc>>b;
        if(b-a>=vc-va)cout<<vc;//第一种情况
        else cout<<va+(b-a);//第二种情况
        cout<<endl;//别忘了换行
    }
    return 0;
}
```

---

## 作者：int_stl (赞：0)

这道题的思路如下：
- 首先判断 $b-a>v_c-v_a$，如果真，$v_b=v_c$，因为 $v_c$ 是 Alex 第 $c$ 天读的章节，所以在 $c$ 天之前（包括 $c$ 天），他都会阅读 $v_c$。
- 否则，$v_b = v_a+(b-a)$。因为在 $a$ 天开始，Alex 会按顺序阅读章节，所以在 $a$ 天后的第 $b-a$ 天，他会阅读 $v_a$ 后面的章节。 

由此给出 C++ 和 Kotlin 代码（~~Kotlin 我不会，只好学了一下~~）：  
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a, va, c, vc, b;
        cin >> n;
        cin >> a >> va;
        cin >> c >> vc;
        cin >> b;
        int vb;
        if (b - a >= vc - va) vb = vc;
        else vb = va + (b - a);
        cout << vb << endl;
    }

    return 0;
}

```
```kotlin
import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()

    repeat(t) {
        val n = scanner.nextInt()
        val a = scanner.nextInt()
        val va = scanner.nextInt()
        val c = scanner.nextInt()
        val vc = scanner.nextInt()
        val b = scanner.nextInt()

        val vb: Int
        if (b - a >= vc - va) {
            vb = vc
        } else {
            vb = va + (b - a)
        }
        println(vb)
    }
}

```

---

## 作者：Crasole (赞：0)

## 题意

Alex 买了一本 $n$ 页的小说，为了保证内容的连续性，他不会跳章看，也不会回头看，每一章可能会重复读，但一天不会读多页。第一天他读第 $1$ 章。

已知 Alex 在第 $a$ 天读第 $v_a$ 章，第 $c$ 天读第 $v_c$ 章，请判断在第 $b\ (a < b < c)$ 天他在读第几章，输出任意可能解。

一共有 $T$ 组数据。

## 思路

假设 Alex 每天都只读一章，有两种情况：

- $b - a \ge v_c - v_a$，代表第 $a$ 天至第 $b$ 天的天数比第 $v_a$ 章到第 $v_c$ 章的章节数还要多，也就是说一天读一章很可能没到第 $b$ 天就读完了，那么我们可以让多出来天让 Alex 都读第 $v_c$ 章。

- $b - a < v_c - v_a$，代表每天读一章在第 $b$ 天是读不完的，那么 Alex 就在读第 $v_a + ( b - a )$ 章。

代码非常短小。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,va,c,vc,b;
int main(){
	cin>>t;
	while(t--) {
		cin>>n;
		cin>>a>>va;
		cin>>c>>vc;
		cin>>b;
		if(b-a>=vc-va) cout<<vc;//判断
		else cout<<va+(b-a);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

> Alex 买了一本 $n$ 章的小说，为了保证内容的连续性，他不会跳章看，也不会回头看，每一章可能会读一天或多于一天，但一天不会读多页。第一天他读第 $1$ 章。
>
> 已知 Alex 在第 $a$ 天读第 $v_a$ 章，第 $c$ 天读第 $v_c$ 章，请判断在第 $b\ (a < b < c)$ 天他在读第几章，输出任意可能解。
> 
> 数据范围：$1\le t\le 100$，$1\le n\le 100$，$1\le a\le 98$，$1\le v_a \le a$，$a+2\le c\le 100$，$v_a\le v_c\le c$。

设第 $b$ 天在看 $v_b$ 章，我们注意到符合条件的 $v_b$ 一定满足：

- $v_a \le v_b \le v_c$
  - $v_b$ 一定是第 $v_a$ 章或之后的章节，是第 $v_c$ 章或之前的章节。
- $v_b - v_a \le b - a$
  - 注意到每天最多只能看一章，所以在 $a\sim b$ 天最多只会看 $b - a + 1$ 章，所以要满足 $v_b - v_a + 1 \le b - a + 1$，即 $v_b - v_a \le b - a$。
- $vc - vb \le c - b$
  - 与上一个同理。

那么可以直接在 $v_a$ 和 $v_c$ 之间暴力枚举 $v_b$，判断是否符合第 $2, 3$ 个条件即可。

```kotlin
fun main() {
  val t = readLine()!!.toInt()
  repeat(t) {
    val n = readLine()!!.toInt()
    val (a, va) = readLine()!!.split(' ').map { it.toInt() }.toIntArray()
    val (c, vc) = readLine()!!.split(' ').map { it.toInt() }.toIntArray()
    val b = readLine()!!.toInt()
    for (vb in va..vc) {
      if (vb - va <= b - a && vc - vb <= c - b) {
        println(vb)
        break
      }
    }
  }
}
```

---

## 作者：Berd__ (赞：0)

## 题面大意
### 首先来看一下题面。（加粗为重点）
Alex 买了一本 $n$ 章的小说，为了保证内容的连续性，他**不会跳章看**，也**不会回头看**，每一章可能会读一天或多于一天，但**一天不会读多页**。第一天他读第 $1$ 章。

设 $v_i$ 表示 Alex 第 $i$ 天读的章节，已知 Alex 在第 $a$ 天读第 $v_a$ 章，第 $c$ 天读第 $v_c$ 章，请判断在第 $b$ 天他在读第几章，**输出任意可能解**。

## 思路
因为 Alex 一天不会读超过 $1$ 章，所以如果 $b-a≥v_c-v_a$，答案就是 $v_c$（读到了第 $c$ 天读的章节，就每天重复读此章）。

其余情况就输出 $v_a+(b-a)$（因为从第 $a$ 天开始读，当然就是读到了 $v_a+b-a$ 页啦）。

输出任意解即可。

## 代码
```cpp
#include<iostream>
#define in long long
using namespace std;
int t,n,a,va,c,vc,b;
signed main(){
	cin>>t;
	for(int i=1;i<=t;i++) 
	{
		cin>>n>>a>>va>>c>>vc>>b;
		if(b-a>vc-va) cout<<va+(b-a)<<"\n";
		else cout<<vc<<"\n";
	}
	return 0;
}

```



---

