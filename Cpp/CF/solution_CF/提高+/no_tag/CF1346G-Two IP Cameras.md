# Two IP Cameras

## 题目描述

You have two IP cameras of the same model. Each camera can take photos starting from some moment of time with a fixed period. You can freely choose the starting moment but you can choose the period only as one of $ k $ values $ p_1, p_2, \dots, p_k $ which are chosen by the camera's manufacturer.

You have $ n $ moments of interest $ x_1, x_2, \dots, x_n $ . You'd like to configure both cameras in such a way that at least one camera will take a photo in each of these moments. Configuring the camera means setting the moment when it takes the first photo and the gap between two consecutive photos (which should be one of the values $ p_1, p_2, \dots, p_k $ ). It's not a problem for you that cameras can take photos at other moments of time — you only care about moments of interest.

## 样例 #1

### 输入

```
3 5
3 5 7
1 4 5 7 12```

### 输出

```
YES
1 3
5 7```

## 样例 #2

### 输入

```
3 2
1 2 3
1 10```

### 输出

```
YES
1 1
10 1```

## 样例 #3

### 输入

```
3 4
1 2 3
5 7 9 11```

### 输出

```
YES
5 1
5 1```

## 样例 #4

### 输入

```
3 4
10 20 100
2 3 4 7```

### 输出

```
NO```

# 题解

## 作者：BqtMtsZDnlpsT (赞：2)

一道CF2300，还是主要考察思维，~~以及语言学习能力。~~

我们可以发现，题目转化为：
- 把一个序列分成 $2$ 个子序列。
- 使得在任意一个子序列中，所有数基于模一个给定模数同余，即子序列中每个数两两作差后的最大公约数为某个给定模数的倍数。
- 求模数、余数。

然后我们可以通过严谨的抽屉原理证明 ~~，或是感性理解~~ 发现一个巧妙的定理：
- 若 $n=2$ 则必定有解。
- 否则，若存在一组符合条件的解，定有一个子序列包含 $x_1,x_2$ 或 $x_1,x_3$ 或 $x_2,x_3$

于是，我们在 $n=2$ 时直接特判掉。在 $n>2$ 时考虑含有 $x_1,x_2$ 或 $x_1,x_3$ 或 $x_2,x_3$（下称较小数为 $a$，较大数为 $b$）的那个子序列。我们可以对这三种情况进行分类讨论，每次枚举那个模数，若 $b-a$ 是一个模数的倍数，则在 $x$ 数组中扫一遍，看是否可行（下面具体会讲）。

判断是否可行的过程：
- 首先，我们选出 $x_j$ 使 $x_j-a$ 不为选定模数的倍数（即为不在这个子序列中）。
- 对于这些数，我们要求出第一个数 $front$，以及这些数作差后的最大公约数 $ans$。
- 考虑如何 $O(n)$ 更新 $ans$。我们标记前一个选出的数为 $back$，可以证明若存在解，且模数为 $p_i$，对于之前选出的任意一个 $x_{pos}$ 和当前的 $x_j$ 都有:
$$\left\{\begin{matrix}
\gcd(back-x_{pos},x_j-x_{pos},x_j-back)\equiv 0 \pmod {p_i}\\ 
\gcd(back-x_{pos},x_j-back)\equiv 0 \pmod {p_i}
\end{matrix}\right. $$

- 所以求出所有 $x_j-back$ 的最大公约数的效果与 $ans$ 一样。
- 最后，再枚举 $p_j$，若 $p_j$ 为求出 $ans$ 的约数则存在解。
- 另外还要注意特判没有选出任何数（即第一个子序列即为原序列）、只选出一个数的情况。

下面看代码（个人认为只看上面不看代码比较难懂）：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int k,n,p[100005],x[100005];
int gcd(int u,int v){return !v?u:gcd(v,u%v);}
void check(int a,int b){
	for(int i=1;i<=k;i++){
		if(!((x[b]-x[a])%p[i])){
			int fr=-1,bk=-1,ans=-1;
			for(int j=1;j<=n;j++){
				if((x[j]-x[a])%p[i]){
					if(fr==-1)fr=bk=x[j];
					else{
						if(ans==-1)ans=x[j]-bk;
						else ans=gcd(ans,x[j]-bk);//求所有x_j-back的公约数即可
						bk=x[j];
					}
				}
			}
			if(fr==-1){printf("YES\n%d %d\n%d %d\n",x[a],p[i],x[a],p[i]);exit(0);}//没有数
			else if(ans==-1){printf("YES\n%d %d\n%d %d\n",x[a],p[i],fr,p[1]);exit(0);}//只有一个，不能更新ans
			else{
				for(int j=1;j<=k;j++)
					if(!(ans%p[j])){printf("YES\n%d %d\n%d %d\n",x[a],p[i],fr,p[j]);exit(0);}//找到了
			}
		}
	}
}
int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=k;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]);
	if(n<3){printf("YES\n%d %d\n%d %d\n",x[1],p[1],x[2],p[1]);return 0;}
	check(1,2);
	check(1,3);
	check(2,3);
	puts("NO");
	return 0;
}
```

好！看完代码，有些人可能想问这不是 $O(k(k+n))$ 的复杂度吗，怎么可能过？

当然可以。我们注意到只有 $p_i$ 为 $b-a$ 的约数时才进入下面的循环，而 $1\le x_i\le 10^6$，$1\sim10^6$ 中约数最多的数为 $720720,831600,942480,982800,997920$，约数个数为 $240$，所以总复杂度极限约为 $O(k+240(n+k))$，还是可以过的。

来，交一发！

![](https://cdn.luogu.com.cn/upload/image_hosting/gt9lgufm.png)

诶？打开原题题面，发现只能用 `Kotlin` 这个优（e）秀（chou）的语言，于是我花了好久学习了 `Kotlin` 语言并且过了这题，爱（xian）好（de）学（dan）习（teng）的同学可以也去学。

下面放个AC代码（极（you）其（chou）美（you）观（chang））：
```
private fun readLn()=readLine()!!
private fun readInt()=readLn().toInt()
private fun readStrings()=readLn().split(" ")
private fun readInts()=readStrings().map{it.toInt()}

fun gcd(u:Int,v:Int):Int{
	if(v==0)return u
	else return gcd(v,u%v)
}

fun main(){
	val (k,n)=readInts()
	val p=readInts()
    val x=readInts()
	if(n<=2){
		println("YES")
		println("${x[0]} ${p[0]}\n${x[1]} ${p[0]}")
		return
	}
    var a=0
    var b=1
	for(pi in p){
		if(((x[b]-x[a])%pi)==0){
			var fr=-1
			var bk=-1
			var ans=-1
			for(xj in x){
				if((xj-x[a])%pi!=0){
					if(fr==-1){
                        fr=xj
                    }
					else{
						if(ans==-1)
                            ans=xj-bk
						else    
                            ans=gcd(ans,xj-bk)
					}
                    bk=xj
				}
			}
			if(fr==-1){
				println("YES")
				println("${x[a]} ${pi}\n${x[a]} ${pi}")
				return
			}
			else if(ans==-1){
				println("YES")
				println("${x[a]} ${pi}\n${fr} ${p[1]}")
				return
			}
			else{
				for(pj in p)
					if((ans%pj)==0){
						println("YES")
						println("${x[a]} ${pi}\n${fr} ${pj}")
						return
					}
			}
		}
	}
    a=0
    b=2
	for(pi in p){
		if(((x[b]-x[a])%pi)==0){
			var fr=-1
			var bk=-1
			var ans=-1
			for(xj in x){
				if((xj-x[a])%pi!=0){
					if(fr==-1){
                        fr=xj
                    }
					else{
						if(ans==-1)
                            ans=xj-bk
						else    
                            ans=gcd(ans,xj-bk)
					}
                    bk=xj
				}
			}
			if(fr==-1){
				println("YES")
				println("${x[a]} ${pi}\n${x[a]} ${pi}")
				return
			}
			else if(ans==-1){
				println("YES")
				println("${x[a]} ${pi}\n${fr} ${p[1]}")
				return
			}
			else{
				for(pj in p)
					if((ans%pj)==0){
						println("YES")
						println("${x[a]} ${pi}\n${fr} ${pj}")
						return
					}
			}
		}
	}
    a=1
    b=2
	for(pi in p){
		if(((x[b]-x[a])%pi)==0){
			var fr=-1
			var bk=-1
			var ans=-1
			for(xj in x){
				if((xj-x[a])%pi!=0){
					if(fr==-1){
                        fr=xj
                    }
					else{
						if(ans==-1)
                            ans=xj-bk
						else    
                            ans=gcd(ans,xj-bk)
					}
                    bk=xj
				}
			}
			if(fr==-1){
				println("YES")
				println("${x[a]} ${pi}\n${x[a]} ${pi}")
				return
			}
			else if(ans==-1){
				println("YES")
				println("${x[a]} ${pi}\n${fr} ${p[1]}")
				return
			}
			else{
				for(pj in p)
					if((ans%pj)==0){
						println("YES")
						println("${x[a]} ${pi}\n${fr} ${pj}")
						return
					}
			}
		}
	}
	println("NO")
	return
}
```

---

