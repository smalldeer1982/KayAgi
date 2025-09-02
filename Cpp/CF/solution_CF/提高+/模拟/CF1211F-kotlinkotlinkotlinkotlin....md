# kotlinkotlinkotlinkotlin...

## 题目描述

**请使用 Kotlin 语言**

给出 $n$ 个字符串，将其拼成 ```kotlinkotlin...kotlin``` 的形式。

## 样例 #1

### 输入

```
2
lin
kot
```

### 输出

```
2 1 ```

## 样例 #2

### 输入

```
4
linkotlinkotlinkotl
kotlin
in
kot
```

### 输出

```
2 4 1 3 ```

## 样例 #3

### 输入

```
8
i
n
tlin
o
ko
t
k
l
```

### 输出

```
7 4 3 5 6 8 1 2 ```

# 题解

## 作者：L01001101 (赞：1)

[$\color{000000}\text{CF1211F kotlinkotlinkotlinkotlin...}$](https://www.luogu.com.cn/problem/CF1211F)

观察题目，发现一个性质：由于只和字符串首位相关，所以以某个字符 $c$ 结尾的字符串后接的一定是以 $c$ 下一个字符开头的字符串。

举几个例子，以 `t` 结尾的字符串，后面一定接的是以 `l` 开头的字符串；以 `n` 结尾的字符串，后面一定接的是以 `k` 开头的字符串。

这让我们不禁想到了一些类似的题目，例如：[$\color{000000}\text{P1127 词链}$](https://www.luogu.com.cn/problem/P1127)。

考虑使用相同的方法来解决问题，显然我们可以对于每个字符串按照前面的解决方式建出一条边：开头的字符连向结尾字符的下一个字符。

按照上述方式建完图后跑欧拉回路即可。

需要注意的是，由于输出的是字符串编号，我们在边上需要记录编号，跑欧拉回路是输出编号。

时间复杂度 $O(n)$。

```kotlin
fun main(){
	val n=readLine()!!.toInt()
    val e=Array(6){ArrayList<Pair<Int,Int>>()}
    (1..n).forEach{
        val s=readLine()!!
        val u="kotlin".indexOf(s[0])
        val v=(u+s.length)%6
        e[u].add(v to it)
    }
    val ans=ArrayList<Int>()
    fun dfs(u:Int){
        while(!e[u].isEmpty()){
            val (v,id)=e[u].removeAt(e[u].size-1)
            dfs(v)
            ans.add(id);
        }
    }
    dfs(0);
    println(ans.reversed().joinToString(" "))
}
```

为了方便理解，附上 C++ 代码（细节有所差异）。

```cpp
#include<cstdio>
#include<cstring>
const int N=10,S=3e5+10,M=1e5+10;
int n;
char s[S];
int stk[M],top;
int head[N],tot;
struct Edge{
	int to,nxt,id;
}e[M];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=0:0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
inline void add(int u,int v,int id){e[++tot]=(Edge){v,head[u],id},head[u]=tot;}
inline int get(char c){
	if(c=='k')return 1;
	else if(c=='o')return 2;
	else if(c=='t')return 3;
	else if(c=='l')return 4;
	else if(c=='i')return 5;
	else return 6;
}
inline void dfs(int u){
	for(int i=head[u];i;i=head[u])
		head[u]=e[i].nxt,dfs(e[i].to),stk[++top]=e[i].id;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)
		scanf("%s",s+1),add(get(s[1]),get(s[strlen(s+1)])%6+1,i);
	dfs(1);
	while(top)printf("%d\n",stk[top--]);
	return 0;
}
```

---

## 作者：Lpttor (赞：1)

### 题意简述
给出 $n$ 个字符串，将其拼成 ```kotlinkotlin...kotlin``` 的形式。

### 解题思路
将每一个字符串看成一条边，比如 kotl 是从 k 到 i 的边，ink 是从 i 到 o 的边，otlin 是从 o 到 k 的边。

于是我们得到了一个有向图，而题目则是要求我们求一条欧拉回路。

>如果图G中的一个路径包括每个边恰好一次，则该路径称为欧拉路径。 ——百度百科

求欧拉回路可以用 Fleury 算法或 Hierholzer 算法，这里介绍后者。

题目保证了欧拉回路存在，所以从 k 节点开始 DFS ，每次随意选择一条出边，删除已走过的边，直到回到 k. 这样我们就得到了一条回路。

接下来在这条路径上寻找仍有出边的点，从它开始同样 DFS 寻找一条回路，将它加入路径中。比如 0 -> 1 -> 4 -> 0 ，如果 1 还有出边，找到一条回路 1 -> 2 -> 3 -> 1，那么加入后就变成 0 -> 1 -> 2 -> 3 -> 1 -> 4 -> 0.

当路径上所有的点都没有出边时，得到的路径就是欧拉回路。

这个算法的复杂度是 $O(n)$ ，但是我写的是每次找到新的回路就从路径开头重新开始判断，最差情况的时间复杂度是$O(n^2)$. ~~主要原因是不会用 Kotlin~~

AC代码：
```java
import java.util.*
data class edge (var to:Int,var index:Int)
fun place(ch:Char):Int{
    when(ch){
        'k' -> return 0
        'o' -> return 1
        't' -> return 2
        'l' -> return 3
        'i' -> return 4
        else -> return 5
    }
}
var graph=Array(6) { mutableListOf<edge>() }
fun findloop(st:Int):LinkedList<edge>{
    var ptr=graph[st][0].to
    var ptro:Int
    var ret=LinkedList<edge>()
    ret.add(graph[st][0])
    graph[st].removeAt(0)
    while(ptr!=st){
        ret.add(graph[ptr][0])
        ptro=ptr
        ptr=graph[ptr][0].to
        graph[ptro].removeAt(0)
    }
    return ret
}
fun main(args:Array<String>) {
    val sc = Scanner(System.`in`)
    var route = LinkedList<edge>()
    var n = sc.nextInt()
    var flag = true
    var temp: String
    sc.nextLine()	//消除回车
    for (i in 1..n) {
        temp = sc.nextLine()
        graph[place(temp[0])].add(edge((place(temp.last())+1)%6,i))
    }
    route = findloop(0)
    while (flag) {
        flag = false
        if (graph[0].size != 0) {
            route.addAll(0, findloop(0))
            flag = true
        } else for (i in route) {
            if (graph[i.to].size != 0) {
                route.addAll(route.indexOf(i) + 1, findloop(i.to))
                flag = true
                break
            }
        }
    }
    for (i in route) {
        print(i.index)
        print(" ")
    }
    println("")
}
```

---

