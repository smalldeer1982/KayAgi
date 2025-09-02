# Dice Tower

## 题目描述

A dice is a cube, its faces contain distinct integers from 1 to 6 as black points. The sum of numbers at the opposite dice faces always equals 7. Please note that there are only two dice (these dices are mirror of each other) that satisfy the given constraints (both of them are shown on the picture on the left).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF225A/85f2da947143b29924bb6531722e86105dbf28c1.png)Alice and Bob play dice. Alice has built a tower from $ n $ dice. We know that in this tower the adjacent dice contact with faces with distinct numbers. Bob wants to uniquely identify the numbers written on the faces of all dice, from which the tower is built. Unfortunately, Bob is looking at the tower from the face, and so he does not see all the numbers on the faces. Bob sees the number on the top of the tower and the numbers on the two adjacent sides (on the right side of the picture shown what Bob sees).

Help Bob, tell whether it is possible to uniquely identify the numbers on the faces of all the dice in the tower, or not.

## 样例 #1

### 输入

```
3
6
3 2
5 4
2 4
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
3
2 6
4 1
5 3
```

### 输出

```
NO```

# 题解

## 作者：Tobiichi_Origami (赞：1)

**这是一道很有意思的题**

**思路**

这道题要把可能是 $\texttt{NO}$ 都一一列举出来，如果符合，则输出 $\texttt{NO}$，否则输出 $\texttt{YES}$。

首先，我们要知道，每个骰子的顶部和底部都是一样的，因为上一个骰子的底部和这一个骰子的底部的和也是 $7$。然后，骰子的六个面都不能相等，所以 $x$ 不能等于 $y$，并且 $x$ 和 $y$ 也不能等于 $top$。之后，骰子的每一面相对的两面和为 $7$，所以我们可以得出  $x$ 和 $y$ 均不可以在 $top$ 的对立面，并且 $x$ 和 $y$ 也不可以在互相的对立面。然后就做完了。

**贴代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,top,x,y;
    cin>>n>>top;
    while(n--)
    {
        cin>>x>>y;
        if(x==y||x==top||y==top||x==7-top||y==7-top||x+y==7)
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```



---

## 作者：Shimotsuki (赞：1)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF225A)

[传送门 to CF](http://codeforces.com/problemset/problem/225/A)
## Part 0
这道题的大致思路便是把 NO 的可能性全部列出，经过枚举后还未被排除的就是 YES。
## Part 1
因为骰子上六个面的数字各不相同，所以可以想到的就是如果看到的两个侧面上的数字相等，那就一定不相等。

本部分代码实现：
```cpp
if(a==b||a==top_surface||b==top_surface){//两面相同
	return printf("NO")&0;
}
```
## Part 2
与 Part 1 同理，如果两个侧面的数字会与底面的数字相等，那也一样不成立。已知顶面及顶面与底面的和为七，就可以求出底面。

本部分代码实现：
```cpp
else if(a==bottom||b==bottom){//与对面数作比较
	return printf("NO")&0;
}
```
## Part 3
Part 1 与 Part 2 已经列举出了所有不成立的可能，那么剩下的便都是成立的。

$Code$
```cpp
#include<cstdio>

using namespace std;

#define rd(x) x=read()

inline int read(){//快读优化 
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	int n,a,b,top_surface,bottom;
	rd(n);rd(top_surface);
   	bottom=7-top_surface;//计算底面
	while(n--){
		rd(a);rd(b);
		if(a==b||a==top_surface||b==top_surface){//两面相同 
			return printf("NO")&0;
		}
		else if(a==bottom||b==bottom){//与对面数作比较 
			return printf("NO")&0;
		}
	}
	return printf("YES")&0;
}
```


---

## 作者：REAL_曼巴 (赞：1)

此题是一道立体数学题。题目给了我们一个很关键的条件：两个面之和为七。那么，我们可以知道，七减输入的数就可以知道他对面（看不见的）的数是多少。但是，此题还有一个关键：贴在一起的两面点数相同。这样，我们就可以也推出每一颗骰子的所有面了。剩下的，就是要推断出有没有骰子的两面点数相同了。

```
#include<iostream>
using namespace std;
int main(){
	int n,a,b,c;
	cin>>n;
	cin>>c;
    int dimian=7-n;//计算底面
    bool f=1;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(a==b||a==c||b==c||a==dimain||b==dimian){f=0;break;}//标记，相同
	}
    if(f)
	cout<<"YES"<<endl;
    else
    cout<<"NO"<<endl;
	return 0;
}

```


---

## 作者：Firstly (赞：0)

这是一道考察思维的好题。

## **题目思路：**

本题问是否可能用正常的骰子摆出骰子塔，即数据中所提到的看到的骰子样子是否合法。

如果骰子有任意两个相邻的面是相同的，或任意两个相邻的面互为对面，显然，这是不合法的。

我们通过题目给出的图可以发现，最顶上的骰子给出了相邻的三个面。那么我们可以根据这个骰子推出其余的三个面。这样，最顶上的骰子就被我们全部推出来了。

同时我们也可以发现：贴在一起的两个面是相等的。由此我们可以推出：相邻的两个骰子，下面的一个的顶面和底面分别对应上面一个的底面和顶面。这样，我们就可以从上往下推出每一个骰子了。

这时，我们就可以判定已知的相邻的三个面，是否有两个面相等或互为对面。如果是，则无法用正常的骰子摆出骰子塔，直接输出 NO 并退出程序即可。

如果在判定结束后，程序没有结束，即代表骰子塔是可以用正常骰子摆出来的，输出 YES即可。

## **Code:**

```cpp
#include<cstdio>
using namespace std;
int n,dm,x,y;
int main(){
	scanf("%d%d",&n,&dm);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y||x+y==7||x==dm||y==dm||x==7-dm||y==7-dm){
			puts("NO");
			return 0;
		}
	}puts("YES");
	return 0;
}
```


## **反思：**

其实，通过仔细思考可以发现，判定骰子塔合法性的一行代码可以简化。比如顶面和已知的一面相等，已知的一面如果和它的相邻面相等，则它的相邻面一定与顶面相等。这样，我们的代码就可以更加简练了！

---

## 作者：_easy_ (赞：0)

# 思路
两个正常的骰子在叠成如题目所示的塔型时，可以发现两个接触面上的数是一样的。

所以我们只需要在输入的时候判断一下。如果输入的两个面其中的一个和最顶上或最顶上的对面，如果是就直接输出 $\texttt{No}$，否则跳过。如果一直到最后都没有输出 $\texttt{No}$，就输出 $\texttt{Yes}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a,b;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(a==b||a==k||b==k||a==7-k||b==7-k){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：hanyuchen2019 (赞：0)

## CF225A Dice Tower

### part 1

一个正常的骰子每面上的点数在 $1...6$ 之间，不重不漏，且相对的两面和为 $7$ 。（废话）

题中的“骰子塔”有一个坑点：两颗骰子贴在一起的两面点数相同。

### part 2

题中让我们判断是否有可能用正常的骰子叠出描述中的骰子塔，也就是要根据已知的信息推断出有没有骰子的两面点数相同。

首先，可以根据前面和右面的点数用 $7-a$ 算出后面和左面的点数。

其次，我们已知最上面的点数，可以求出底面的点数，而且此题中有一个隐藏条件：**两颗骰子贴在一起的两面点数相同**，也就可以推出每一颗骰子的所有面了。

### part 3 Code

```cpp
#include<iostream>
#define reg register int
#define dm(n) (7-n)//一个宏定义，值是 n 对面的点数
using namespace std;
int main()
{
 	ios::sync_with_stdio(false);
	int n,a,b,c;
	cin>>n;
	cin>>c;//c 是顶面
	for(reg i=1;i<=n;i++)
	{
		cin>>a>>b;
		if(a==b||a==c||b==c||a==dm(c)||b==dm(c))
        	//判重，其实还要写c==dm(a)||c==dm(a)，但与最后两条等价
		{
			cout<<"NO"<<endl;
			return 0;//直接return，不用执行了
		}
	}
	cout<<"YES"<<endl;
	return 0;
}

```

---

## 作者：pitiless0514 (赞：0)

## CF225A Dice Tower

#### 1.题目简述：
有 $n$ 个骰子被叠在了一起。对于每个骰子上的一个数，与它对面的数的和始终为 $7$ 。

你是小明，你只能从正面看这个骰子塔，你看到了每一个骰子的两面 $a$ 与 $b$ 。以及最顶上的数。

试问是否有可能用正常的骰子叠出描述中的骰子塔？

如果可以输出 $\text{YES}$ ，否则输出 $\text{NO}$  。

#### 2.解析：

问你是否能用正常的骰子堆出描述中的塔，那就是判断是否这个塔里会有不正常的骰子，也就是不是每个面的数字互不相同。

我们发现我们知道了顶上骰子的三个面，那么我们根据面对面的数字和为 $7$ 。可以把第一个骰子的六面确定。

然后，这时第二个骰子的六面中也有三面被确定了。然后就可以往下做。

那么我们就只需要判定是否有一个骰子中有两面是相同的。

由于我们已知合法两面，那我们只用判断这两面是否有一面的值为骰子的顶部元素或者骰子的底部元素即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300;
int n,x,y;
struct node{
	int a,b;
}f[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>x;
	y=7-x;
	for(int i=1;i<=n;i++){
		cin>>f[i].a>>f[i].b;
		if(f[i].a==x||f[i].a==y){
			printf("NO");return 0;
		}
		if(f[i].b==x||f[i].b==y){
			printf("NO");return 0;
		}
	}
	printf("YES");
	return 0;
}
```

---

