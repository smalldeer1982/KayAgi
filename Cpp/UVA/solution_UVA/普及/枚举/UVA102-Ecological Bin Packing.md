# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10```

### 输出

```
BCG 30
CBG 50```

# 题解

## 作者：pyyyyyy (赞：5)

# 题解 UVA102

>由于有三种颜色需要区分开来，故总共有六种情况，而且题目要求输出最小的移动的次数，若次数相同则按字典序输出第一个最小的，故我们可以开一个数组存储按字典序排好所有情况的状态！

~~~cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<string>
#include<cstring>
char str[6][5]={"BCG","BGC","CBG","CGB","GBC","GCB"};
long n[3][3],js[6];
int main()
{
	long int i,min,p;
	while(scanf("%ld%ld%ld%ld%ld%ld%ld%ld%ld",&n[0][0],&n[0][1],&n[0][2],&n[1][0],&n[1][1],&n[1][2],&n[2][0],&n[2][1],&n[2][2])!=EOF)
	{
		js[0] = n[1][0] + n[2][0] + n[0][2] + n[2][2] + n[0][1] + n[1][1];
        js[1] = n[1][0] + n[2][0] + n[0][1] + n[2][1] + n[0][2] + n[1][2];
        js[2] = n[1][2] + n[2][2] + n[0][0] + n[2][0] + n[0][1] + n[1][1];
        js[3] = n[1][2] + n[2][2] + n[0][1] + n[2][1] + n[0][0] + n[1][0];
        js[4] = n[1][1] + n[2][1] + n[0][0] + n[2][0] + n[0][2] + n[1][2];
        js[5] = n[1][1] + n[2][1] + n[0][2] + n[2][2] + n[0][0] + n[1][0];
		min=js[0];
		p=0;
		for(i=1;i<6;i++)
			if(js[i]<min)
			{
				min=js[i];
				p=i;
			}
		printf("%s %ld\n",str[p],js[p]);
	}
	return 0;
}


~~~
来源：csdn

---

## 作者：Prms_Prmt (赞：4)

# 题解之 `UVa 102`

0. **我的博客**

请参见 [更佳体验链接](https://www.luogu.com.cn/blog/PrmsPrmt/uva-102-post)。

---
1. **函数介绍**

首先介绍求 _下一排列_ 的 `C++98/03` 中加入的的 `STL` 函数。

```cpp
next_permutation(起始地址，末位地址+1);
```
该函数会生成一个序列的**全排列**，并找到当前排列的下一排列。

如果上一个排列是序列中最大的，它返回 `false`，否则为 `true`。

它直接**改变**数组元素顺序，类似排序函数 `sort(起始地址，末位地址+1)`。

与它相似的生成 _上一排列_ 函数是：

`prev_permutation(起始地址，末位地址+1);`

_二者使用前都不用排序。_
 
`DFS` 全排列时间复杂度都是 $ Θ(n!) $。

---

2. **函数运用**

遍历全排列的应用：

```cpp
do
{
	;//处理。
    
}while(next_permutation(起始地址,末尾地址+1)); //下一排列。

//或者……
do
{
	;//处理。
   
}while(prev_permutation(起始地址,末尾地址+1)); //上一排列。

```
---
3. **题目分析**

首先设参，方便列式。

_解：_

令 $i$ 箱放 $a[i]$ 色玻璃；

令 $t[a[i]]$ 为 $a[i]$ 色玻璃的总数；

令 $i$ 箱内第 $a$ 种玻璃数量为 $b[i][a]$；

令每种排列的代价为 $ans$；

令解为 $res$。

再用 $t[a[i]]$ 减 $b[i][a]$，就是需要搬动的 $a[i]$ 色玻璃，求和后得：

$${ans}=\sum_{i=0}^{i<3}t[a[i]]-b[i][a]$$

借助这个函数**遍历 $a$ 序列的全排列**，用上式算出每种排列的 ${ans}$ 值。

最后在每种排列的 $ans$ 中求出最小值，记录最优排列，即：

$$res=\min\{ans\}$$

本题中，项数 `n=3`，时间复杂度 $Θ(n!\times n)$，可解。

解毕。

---

4. **代码部分**

```cpp
#include <bits/stdc++.h>
#define int long long //宏定义
using namespace std;
int b[3][3];                 //每个箱子里每种玻璃数量
int t[3];                    //统计每种玻璃总数
char a[3] = {'B', 'C', 'G'}; //待求全排列数组，代表种类
string str;                  //最优解排列字符串
int res;                     //所有 ans 中最优解
bool scan(void)              //读入函数
{
    res = INT_MAX;
    t[0] = t[1] = t[2] = 0;
    //初始化
    return EOF != scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &b[0][0], &b[0][1], &b[0][2], &b[1][0], &b[1][1], &b[1][2], &b[2][0], &b[2][1], &b[2][2]);
    //读入并检测是否到文件末尾
    //EOF：End Of File 文件末尾
    //或用 return (cin>>...>>...>>...);
}
main() //C 风格，出自《C++ Primer Plus》
{      //不能再用 int，int 被宏定义 long long
    while (scan())
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                t[j] += b[i][j]; //统计每种玻璃总数
        int id = 0, ans;
        do
        {
            ans = 0;                    //记录本次代价 ans
            for (int i = 0; i < 3; i++) //枚举三个箱子
            {
                if (a[i] == 'B')
                    id = 0;
                else if (a[i] == 'G')
                    id = 1;
                else
                    id = 2;                //种类编号对应
                ans += (t[id] - b[i][id]); //代价累加，见公式
            }
            if (res > ans) //更新答案
            {
                res = ans; //记录最优解
                str = a;   //记录最优排列
                           //char[] 能对 string 赋值
                           //string 不能对 char[] 赋值
            }
        } while (next_permutation(a, a + 3)); //全排列
        cout << str << ' ' << res << endl;    //解毕
    }
    return 0;
}

```
---

5. **结尾片语**

才疏学浅，若有不妥，请于评论指点，感激不尽。

部分 `next_permutation()` 函数资料参考于 `C 语言中文网`。

### 最重要的是：谢谢！

---

## 作者：Zenith_Yeh (赞：3)

这是道水题，用数组存一下状态即可。共有 $A_3^3=6$ 种情况。

**上菜**
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	if(c==EOF)exit(0);//记住一定要这行，不然快读不会停止。
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
string s[6]={"BCG","BGC","CBG","CGB","GBC","GCB"};//六种情况。
long long a[3][3],cs[6],minn,top;
int main()
{	while(1)
	{	a[0][0]=read(),a[0][1]=read(),a[0][2]=read(),a[1][0]=read(),a[1][1]=read(),a[1][2]=read(),a[2][0]=read(),a[2][1]=read(),a[2][2]=read();
		minn=1000000000000000000;
		cs[0]=a[1][0]+a[2][0]+a[0][2]+a[2][2]+a[0][1]+a[1][1];//记一下。
        cs[1]=a[1][0]+a[2][0]+a[0][1]+a[2][1]+a[0][2]+a[1][2];
        cs[2]=a[1][2]+a[2][2]+a[0][0]+a[2][0]+a[0][1]+a[1][1];
        cs[3]=a[1][2]+a[2][2]+a[0][1]+a[2][1]+a[0][0]+a[1][0];
        cs[4]=a[1][1]+a[2][1]+a[0][0]+a[2][0]+a[0][2]+a[1][2];
        cs[5]=a[1][1]+a[2][1]+a[0][2]+a[2][2]+a[0][0]+a[1][0];
		for(register int i=0;i<=5;++i)
			if(cs[i]<minn)minn=cs[i],top=i;//比较。
		cout<<s[top];
		printf(" %lld\n",cs[top]);
	}
	return 0;
}
```


---

## 作者：lifetime (赞：1)

题目给的数据太少，可以得知总共有6种情况，本人给的代码可以稍加修改数值应用更多情况，究其本质即为DFS问题，找出其最长路径后，总数值减去最长路径即为所求答案，唯一字符串处理有点麻烦。

```java
import javax.swing.plaf.basic.BasicInternalFrameTitlePane;
import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.*;

public class Main {
    static ArrayList<Integer> move = new ArrayList<>();
    static int maxpathsize = Integer.MIN_VALUE;
    static int[][] arr = new int[3][3];
    static HashSet<Integer> isuse = new HashSet<>();
    static PriorityQueue<String> bottlleType = new PriorityQueue<>();
    static String[] type = {"B", "G", "C"};

    public static void dfs(int bin, String s) {
        if (bin == 3) {
            int x = 0;
            for (int i = 0; i < move.size(); i++) {
                x += move.get(i);
            }
            if (x >maxpathsize) {
                bottlleType.clear();
                maxpathsize = x;
                bottlleType.add(s);
            } else if (x == maxpathsize)
                bottlleType.add(s);
        } else {
            for (int i = 0; i < 3; i++) {
                if (!isuse.contains(i)) {
                    isuse.add(i);
                    move.add(arr[bin][i]);
                    s += type[i];
                    dfs(bin + 1, s);
                    move.remove(move.size() - 1);
                    isuse.remove(i);
                    s = s.replace(type[i], "");
                }
            }
        }
    }

    public static void init() {
        isuse.clear();
        move.clear();
        bottlleType.clear();
        maxpathsize = Integer.MIN_VALUE;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            init();
            int sum = 0;
            String s = new String();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    arr[i][j] = sc.nextInt();
                    sum += arr[i][j];
                }
            }
            dfs(0, s);
            System.out.print(bottlleType.poll() + " ");
            System.out.println(sum - maxpathsize);
        }
    }
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先输入 $9$ 个数。

设 $a_{i,j}$，代表第 $i$（$0\le i\le2$）号垃圾桶的 $j$ 玻璃瓶数量为$a_{i,j}$。

其中，将 `B G C` 玻璃瓶看做是 `0 1 2` 号。

那么，可以列出 $6$ 种可能：

```
英文  数字
B C G 0 2 1
B G C 0 1 2
C B G 2 0 1
C G B 2 1 0
G B C 1 0 2
G C B 1 2 0
```

对于每种可能，都算一遍花费。花费，就是每个垃圾桶中，需要扔到别的垃圾桶的瓶子的数量之和。

### 2 代码与记录

代码有点难想，建议仔细看，认真想。

```cpp
#include<cstdio>
using namespace std;
int a[3][3];//a[i][j]代表第i垃圾桶的j玻璃瓶数量
//0 B  1 G  2 C
int c;//花费
int mi;//最少花费的方案
int ans;//最少的花费
char ch[6][5]={"BCG","BGC","CBG","CGB","GBC","GCB"};//6种方案
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA00102_1.in","r",stdin);
	freopen("UVA00102_1.out","w",stdout);
	#endif
	while(scanf("%d%d%d%d%d%d%d%d%d",&a[0][0],&a[0][1],&a[0][2],&a[1][0],&a[1][1],&a[1][2],&a[2][0],&a[2][1],&a[2][2])!=EOF){
		ans=2147483647;//设一个很大的数
		for(int i=0;i<6;++i){
			c=0;
			for(int j=0;j<3;++j){
				if(ch[i][j]=='B'){
					c+=a[j][1]+a[j][2];
				}
				if(ch[i][j]=='C'){
					c+=a[j][0]+a[j][1];
				}
				if(ch[i][j]=='G'){
					c+=a[j][0]+a[j][2];
				}
			}
			if(ans>c){
				mi=i;
				ans=c;
			}
		}
		printf("%s %d\n",ch[mi],ans);
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/52694735)

By **dengziyue**

---

## 作者：Loxilante (赞：0)

一道比较水的黄题，开始看还是没什么头绪哒，不过思路出来之后写起来就很简单啦：

```cpp
#include <bits/stdc++.h>
using namespace std;
// B 棕 G 绿 C 透明 input: BGC
const string str[] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"}; // 存6种情况，注意要按字典序~
int mapping[256]; // 存三种颜色在每个桶里的位置
int w[20], u[20];
signed main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	mapping['B'] = 0;
	mapping['G'] = 1;
	mapping['C'] = 2;
	while(cin>>w[0]>>w[1]>>w[2]>>w[3]>>w[4]>>w[5]>>w[6]>>w[7]>>w[8]) // 暂时没想到什么更好的输入方法...
	{
		string ansStr; // 用来存储答案
		int minw = 1<<30; // 记得赋INF~
		for(int i = 0; i < 6; i++) // 循环6种情况
		{
			string now = str[i]; // 现在情况
			int cnt = 0;
			for(int i = 0; i < 3; i++) u[now[i]] = i*3+mapping[now[i]]; // u数组中存放不需要移动(累加)的w数组下标
			int temp[] = {u['B'], u['G'], u['C']}; // 把3个不需要移动的下标集中到temp
			sort(temp, temp+3);
			for(int i = 0; i < 3; i++) if (i != temp[0]) cnt += w[i];
			for(int i = 3; i < 6; i++) if (i != temp[1]) cnt += w[i];
			for(int i = 6; i < 9; i++) if (i != temp[2]) cnt += w[i];
			if (minw > cnt) minw = cnt, ansStr = str[i];
		}
		cout<<ansStr<<' '<<minw<<endl;
	}
	return 0; // 完结撒花~
}
```

---

## 作者：Nozebry (赞：0)

## Problems
题目会给出若干组数据，每组数据都有 $9$ 个数，现在要你求用最少的移动步数，使得每个垃圾桶只包含一种颜色的瓶子
## Answer
由于题目中只有 $3$ 种颜色的玻璃，分别为棕色($B$)，绿色($G$)和透明($C$)，通过排列我们可以发现，将三种颜色排列只有以下 $6$ 种情况：$BCG,BGC,CBG,CGB,GBC,GCB$

接下来问题就变得简单了，我们只需要根据以上 $6$ 种排列去枚举 $6$ 种不同的方案，然后再进行比较，得到最小比较次数在数组里的位置。最后输出即可

## Code
```pascal
var
    i,min,k:longint;
    f:array[0..6]of longint;
    a:array[1..3,1..3]of longint;
    s:array[1..6]of string=('BCG','BGC','CBG','CGB','GBC','GCB');//将6种情况存好
begin
    while not eof do//因为数据的组数不清楚，所以需要用eof来判断文件是否结束
    begin
        readln(a[1,1],a[1,2],a[1,3],a[2,1],a[2,2],a[2,3],a[3,1],a[3,2],a[3,3]);//表示每种颜色所能接受的瓶子数
	f[1]:=a[1,2]+a[1,3]+a[2,1]+a[2,2]+a[3,1]+a[3,3];
        f[2]:=a[1,2]+a[1,3]+a[2,1]+a[2,3]+a[3,1]+a[3,2];
        f[3]:=a[1,1]+a[1,2]+a[2,2]+a[2,3]+a[3,3]+a[3,1];
        f[4]:=a[1,1]+a[1,2]+a[2,1]+a[2,3]+a[3,3]+a[3,2];
        f[5]:=a[1,1]+a[1,3]+a[2,2]+a[2,3]+a[3,2]+a[3,1];
        f[6]:=a[1,1]+a[1,3]+a[2,1]+a[2,2]+a[3,2]+a[3,3];//以上6句为计算每种排列所得到的交换次数
	min:=f[1];k:=1;
	for i:=2 to 6 do
	        if(f[i]<min) then
		begin
		        min:=f[i];
			k:=i;
		end;//找到最小的交换次数
	writeln(s[k],' ',f[k]);//输出是那种排列以及这种排列的交换次数
    end;
end.

```

---

