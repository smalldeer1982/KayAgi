# Flag Day

## 题目描述

In Berland, there is the national holiday coming — the Flag Day. In the honor of this event the president of the country decided to make a big dance party and asked your agency to organize it. He has several conditions:

- overall, there must be $ m $ dances;
- exactly three people must take part in each dance;
- each dance must have one dancer in white clothes, one dancer in red clothes and one dancer in blue clothes (these are the colors of the national flag of Berland).

The agency has $ n $ dancers, and their number can be less than $ 3m $ . That is, some dancers will probably have to dance in more than one dance. All of your dancers must dance on the party. However, if some dance has two or more dancers from a previous dance, then the current dance stops being spectacular. Your agency cannot allow that to happen, so each dance has at most one dancer who has danced in some previous dance.

You considered all the criteria and made the plan for the $ m $ dances: each dance had three dancers participating in it. Your task is to determine the clothes color for each of the $ n $ dancers so that the President's third condition fulfilled: each dance must have a dancer in white, a dancer in red and a dancer in blue. The dancers cannot change clothes between the dances.

## 样例 #1

### 输入

```
7 3
1 2 3
1 4 5
4 6 7
```

### 输出

```
1 2 3 3 2 2 1 
```

## 样例 #2

### 输入

```
9 3
3 6 9
2 5 8
1 4 7
```

### 输出

```
1 1 1 2 2 2 3 3 3 
```

## 样例 #3

### 输入

```
5 2
4 1 5
3 1 2
```

### 输出

```
2 3 1 1 3 
```

# 题解

## 作者：lrx___ (赞：4)

**题意简述**

有 $N$ 个人和 $M$ 个队伍，一个队伍有 $3$ 个人。一个人可能在多个队伍。要保证每个队伍三个人衣服的颜色各不相同，请求出每个人应该穿什么颜色的衣服。

**思路**

用一个数组记录每个人衣服的颜色。对于每个队伍，如果一个人已经记录衣服的颜色，就标记为这个颜色已用。如果一个人还没有记录，就记录上一个没用过的颜色。

**代码**

```pascal
var
	a:array[1..100005,1..5]of longint;
	c:array[1..100005]of byte;
	vs:array[1..5]of boolean;
	n,m,i,j:longint;
//	c为记录的每个人衣服的颜色，vs[i]表示颜色i是否被访问 
begin
	read(n,m);
	for i:=1 to m do begin
		for j:=1 to 3 do begin
			read(a[i,j]);
		end;
	end;
	for i:=1 to m do begin
		vs[1]:=0;vs[2]:=0;vs[3]:=0;
		for j:=1 to 3 do begin
			vs[c[a[i,j]]]:=true;
//			标记已经记录过的颜色 
		end;
		for j:=1 to 3 do begin
			if(c[a[i,j]]=0)then begin
				if(not vs[1])then begin
					c[a[i,j]]:=1;vs[1]:=true;
				end else if(not vs[2])then begin
					c[a[i,j]]:=2;vs[2]:=true;
				end else begin
					c[a[i,j]]:=3;vs[3]:=true;
				end;
//				如果有人还没记录，就找个没有用过的颜色。 
			end;
		end;
	end;
	for i:=1 to n do begin
		write(c[i],' ');
	end;
end.
```

---

## 作者：Keroshi (赞：3)

# 题意
有 $n$ 个人， $m$ 个三人小组，    
每个小组三个人的数字为 $1$,$2$,$3$,     
求每一个人的数字。
# 分析
先来看一组样例
![](https://cdn.luogu.com.cn/upload/image_hosting/lujp8vxm.png)
需要用 $f$ 数组存储答案，利用贪心的思想，   
第一个小组没有一个人有数字,直接更新。
![](https://cdn.luogu.com.cn/upload/image_hosting/9j3veht1.png)
第二小组有 $3$ 和 $1$ ，会有冲突，   
用过贪心，需要排除 $1$ 和 $3$ 的编号 $1$ 和 $3$ ，这样 $4$ 只能分配 $2$。
![](https://cdn.luogu.com.cn/upload/image_hosting/53ll6eg9.png)
# code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,a[N],f[N],d[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a[1],&a[2],&a[3]);
		memset(d,0,sizeof(d));
		for(int j=1;j<=3;j++)
		    if(f[a[j]]) d[f[a[j]]]=1;//记录是否被分配
		for(int j=1;j<=3;j++)
			if(!f[a[j]]) //给没数字的配分数字
				for(int k=1;k<=3;k++)
					if(!d[k]){
						f[a[j]]=k;
						d[k]=1;
						break;
					}
	}
	for(int i=1;i<=n;i++)
	    printf("%d ",f[i]); 
	return 0;
} 
```

---

## 作者：okra_l (赞：2)

**题意简述**

有 $N$ 个人和 $M$ 个队伍，每个队伍有 $3$ 个人。每个人都有一个标签，每个队伍的三个人标签都不同。只有 $1,2,3$ 三种标签 ，问这些人各自的标签。

**思路**

把每个队伍里面的人判断一遍，如果已经记录过这个人的标签，就给这个标签标记。接下来把没有记录过的人选一个没有标记过的标签记录。最后输出每个人记录的标签即可。

**代码**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[100010][5], f[100010]; // 存储操作和标签信息的数组
bool v[5]; // 标记标签是否已经被使用

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m); // 输入人数n和组数m

    // 读取每个组的信息
    for(i = 0; i < m; i++) {
        for(j = 0; j < 3; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 为每个人分配标签
    for(i = 0; i < m; i++) {
        for(j = 0; j < 3; j++) {
            v[f[a[i][j]]] = 1; // 标记已经被分配的标签
        }
        for(j = 0; j < 3; j++) {
            // 如果当前人还没有被分配标签，根据标签的可用情况进行分配
            if(!f[a[i][j]]) {
                if(!v[1]) {
                    v[1] = 1; // 标签1可用，分配给当前人
                    f[a[i][j]] = 1; // 记录分配给当前人的标签
                } else if(!v[2]) {
                    v[2] = 1; // 标签2可用，分配给当前人
                    f[a[i][j]] = 2; // 记录分配给当前人的标签
                } else {
                    v[3] = 1; // 标签3可用，分配给当前人
                    f[a[i][j]] = 3; // 记录分配给当前人的标签
                }
            }
        }
        v[1] = v[2] = v[3] = 0; // 重置标签可用状态
    }

    // 输出每个人的标签
    for(i = 1; i <= n; i++) {
        printf("%d ", f[i]);
    }

    return 0;
}
```

---

## 作者：Edmundino (赞：1)

# 题意

有 $n$ 个人，$m$ 支队伍，每个队伍有三个人，

而且每个队伍的不同人穿着不同颜色的衣服，

衣服只有三种，分别是 $1,2,3$。

而且每个队伍中最多只有一个人在多个队伍，

求每个人衣服的颜色。

# 分析

贪心即可，

如果，这是第一支队伍，我们不妨把这三个人的衣服设为 $1,2,3$。

以此为基础，

在下面几行队伍中，每行队伍如果出现已经有衣服的人，

那就把那些这支队伍没出现的衣服，给那些还没有分配到衣服的人。

如果这只队伍没有一个人分配到衣服，那就把这三个人分配成 $1,2,3$ 即可。

# 代码

**直接送上$AC$完整代码**

```
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

const int N=1e5+50;

int n,a[4],ma[N],m;//ma[i]表示第i个人穿衣服的颜色

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[1]>>a[2]>>a[3];
		if(i==1)
		{
			ma[a[1]]=1;
			ma[a[2]]=2;
			ma[a[3]]=3;
		 } 
		 else
		 {
		 	if(ma[a[1]]>0)
		 	{
		 		ma[a[2]]=ma[a[1]]+1;
		 		if(ma[a[2]]>3) ma[a[2]]-=3;
		 		ma[a[3]]=ma[a[1]]+2;
		 		if(ma[a[3]]>3) ma[a[3]]-=3;
			 }
			 else
			 {
			 	if(ma[a[2]]>0)
		     	{
		     		ma[a[1]]=ma[a[2]]+1;
		 	    	if(ma[a[1]]>3) ma[a[1]]-=3;
		 	    	ma[a[3]]=ma[a[2]]+2;
		 	    	if(ma[a[3]]>3) ma[a[3]]-=3;
			    }
			    else
			    {
			    	if(ma[a[3]]>0)
		         	{
		  	        	ma[a[2]]=ma[a[3]]+1;
		 	        	if(ma[a[2]]>3) ma[a[2]]-=3;
		 	        	ma[a[1]]=ma[a[3]]+2;
		 	        	if(ma[a[1]]>3) ma[a[1]]-=3;
			        }
			        else
			        {
			        	ma[a[1]]=1;
			        	ma[a[2]]=2;
			        	ma[a[3]]=3;
					}
				}
			 }
		 }
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ma[i]<<" ";
	}
}
```


---

## 作者：Soojin2012 (赞：0)

## 题目简意：
有 $n$ 个人，$m$ 个三人队伍，小组要求每个人的衣服颜色不同，问每个人该穿什么颜色的衣服。
## 题目思路：
贪心，可以开布尔数组记录。对于每个队伍，如果一个人已经记录衣服的颜色，就将这个人记录一下。否则就记录为上一个没用过的颜色。
## AC 代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
#define int long long//define 宏定义 int 为 long long 
int a[10010][5],b[10010];//千万不能开10005，否则你的第7点会RE
bool c[5];
signed main(){//要把int换成signed，不然会编译错误 
    int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=3;j++)cin>>a[i][j];
	}
	for(int i=1;i<=m;i++){
		memset(c,false,sizeof(c));//memset初始化定义d数组为false 
		for(int j=1;j<=3;j++){
		    c[b[a[i][j]]]=true;//记录 
		}
		for(int k=1;k<=3;k++){
			if(!b[a[i][k]]){//给未记录数字分配 
				for(int l=1;l<=3;l++){
					if(!c[l]){
						b[a[i][k]]=l;
						c[l]=1;
						break;//找到后继续下一个 
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
	    cout<<b[i]<<" ";//记得输出空格，这个人忘记写了导致WA
	}
	return 0;
}
```


---

## 作者：king_xuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF357B)

# 题意
有 $n$ 个人，$m$ 个队伍，每个队伍有 $3$ 个人。每个队伍人穿着的衣服的颜色（$1$,$2$,$3$）不同。

求每个人衣服的颜色。(看了 Edmundino 大佬的题解，才知道“每个队伍中最多只有一个人在多个队伍”，谢谢大佬)

# 分析
这个问题可以使用回溯法来解决。我们可以定义一个递归函数，每次选择一个数字给一个人，并检查是否满足条件。如果满足条件，则继续递归下一个人；如果不满足条件，则回溯到上一个选择，尝试其他数字。

# 代码

```
#include<bits/stdc++.h>//万能头 
using namespace std;
#define int long long//建议大家都写上,毕竟"十年OI一场空,不开long long见祖宗"
int n,m;
int a[10010],f[10010],d[10010];
signed main(){//记得将int换成signed 
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[1]>>a[2]>>a[3];
		memset(d,0,sizeof(d));//初始化 
		for(int j=1;j<=3;j++){
		    if(f[a[j]]) d[f[a[j]]]=1;
		}
		for(int j=1;j<=3;j++){
			if(!f[a[j]]){
				for(int k=1;k<=3;k++){
					if(!d[k]){
						f[a[j]]=k;
						d[k]=1;
						break;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
	    cout<<f[i];
	}
	return 0;//return 0养成好习惯 
} 
```

---

