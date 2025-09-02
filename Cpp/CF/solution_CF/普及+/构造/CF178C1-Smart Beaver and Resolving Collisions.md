# Smart Beaver and Resolving Collisions

## 题目描述

The Smart Beaver from ABBYY has a lot of hobbies. One of them is constructing efficient hash tables. One of the most serious problems in hash tables is resolving collisions. The Beaver is interested in this problem very much and he decided to explore it in detail.

We assume that the hash table consists of $ h $ cells numbered from $ 0 $ to $ h-1 $ . Objects are added to and removed from it. Every object has its own unique identifier. In addition, every object has a corresponding hash value — an integer between $ 0 $ and $ h-1 $ , inclusive. When an object is added to the table, if the cell corresponding to the hash value of the object is free, then this object goes there. If the cell is already occupied by another object, there is a collision. When an object is deleted from the table, the cell which it occupied becomes empty.

The Smart Beaver has recently learned about the method of linear probing to resolve collisions. It is as follows. Let's say that the hash value for the added object equals $ t $ and cell $ t $ of the table is already occupied. Then we try to add this object to cell $ (t+m) mod h $ . If it is also occupied, then we try cell $ (t+2·m) mod h $ , then cell $ (t+3·m) mod h $ , and so on. Note that in some cases it's possible that the new object can not be added to the table. It is guaranteed that the input for this problem doesn't contain such situations.

The operation $ a mod b $ means that we take the remainder of the division of number $ a $ by number $ b $ .

This technique immediately seemed very inoptimal to the Beaver, and he decided to assess its inefficiency. So, you are given a sequence of operations, each of which is either an addition of an object to the table or a deletion of an object from the table. When adding a new object, a sequence of calls to the table is performed. Calls to occupied cells are called dummy. In other words, if the result of the algorithm described above is the object being added to cell $ (t+i·m) mod h $ $ (i>=0) $ , then exactly $ i $ dummy calls have been performed.

Your task is to calculate the total number of dummy calls to the table for the given sequence of additions and deletions. When an object is deleted from the table, assume that no dummy calls are performed. The table is empty before performing the operations, that is, initially it doesn't contain any objects.

## 样例 #1

### 输入

```
10 2 7
+ 11 0
+ 22 2
+ 33 6
+ 44 0
+ 55 0
- 22
+ 66 0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 1 6
+ 123 0
+ 234 1
+ 345 2
- 234
+ 456 0
+ 567 0
```

### 输出

```
4
```

# 题解

## 作者：Michael1234 (赞：2)

- 本题可以使用**模拟**的思路：

- 当操作为 `+ id hash` 时，如果归属与 `hash` 的隔间为空，直接记录 $book_{hash}=true$，$mp_{id}=hash$。

- 否则发生了**哈希冲突**，从 $1$ 到 $n$ 枚举 $i$。直到 $book_{(hash+i\times m) \bmod h}=false$ 为止，否则其在不停发生**哈希冲突**，需不断累积答案，最后记录 $book_{(hash+i\times m) \bmod h}=true$，$mp_{id}=(hash+i\times m)\bmod h$。

- 当操作为 `- id` 时，直接记录 $book_{mp_{id}}=false$。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int h,m,n,id,hsh,ans;
map<int,int>mp;//防越界
bool book[N];//防超时
char ch;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>h>>m>>n;
	while(n--)
	{
		cin>>ch;
		if(ch=='+')
		{
			cin>>id>>hsh;
			if(book[hsh])//发生哈希冲突
			{
				++ans;//累计答案
				for(int i=1;;i++)
				{
					if(!book[(hsh+i*m)%h])//可以操作
					{
						book[(hsh+i*m)%h]=true;
						mp[id]=(hsh+i*m)%h;
						break;//记录并终止循环
					}
					++ans;//否则发生了哈希冲突，累计答案
				}
			}
			else//直接记录即可
			{
				book[hsh]=true;
				mp[id]=hsh;
			}
		}
		else
		{
			cin>>id;
			book[mp[id]]=false;
		}
	}
	cout<<ans;
	return 0;
}
~~~

---

## 作者：Phoenix114514 (赞：0)

# CF178C1 Smart Beaver and Resolving Collisions
模拟就能过。
## 思路
将哈希表记为 $b$ 数组，用一个 map $m$ 维持，每次操作如下：
- ```+ id hash```，若 $b_{hash}$ 的位置为空， $b_{hash}=1$，$m_{id}=hash$。若不为空，即发生哈希冲突，枚举 $i$ 从 $1$ 开始，直到 $b_{hash+i \times m}=0$，并且每次答案加一。
- ```- id```，$b_{m_{id}}=0$，直接移除。
## Code
```cpp
#include<bits/stdc++.h>
#include<bits/stl_algo.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
//#pragma GCC optimize(3)
using namespace std;
#define ll long long
#define ull unsigned long long
#define ui unsigned int
const int N=2e5+5;
int h,m,n,ans;
map<int,int> mp;
bool b[N];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>h>>m>>n;
    while(n--){
        char opt;
        cin>>opt;
        if (opt=='+'){
            int id,ha;
            cin>>id>>ha;
            if (!b[ha])b[ha]=true,mp[id]=ha;
            else{
                ans++;
                for (int i=1;;i++){
                    if (!b[(i*m+ha)%h]){
                        b[(i*m+ha)%h]=true;
                        mp[id]=(i*m+ha)%h;
                        break;
                    }
                    ans++;
                }
            }
        }else{
            int id;
            cin>>id;
            b[mp[id]]=false;
        }
    }
    cout<<ans;
    return 0;
}
```

---

