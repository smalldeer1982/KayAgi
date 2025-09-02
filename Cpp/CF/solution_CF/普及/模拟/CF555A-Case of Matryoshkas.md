# Case of Matryoshkas

## 题目描述

Andrewid the Android is a galaxy-famous detective. He is now investigating the case of vandalism at the exhibition of contemporary art.

The main exhibit is a construction of $ n $ matryoshka dolls that can be nested one into another. The matryoshka dolls are numbered from $ 1 $ to $ n $ . A matryoshka with a smaller number can be nested in a matryoshka with a higher number, two matryoshkas can not be directly nested in the same doll, but there may be chain nestings, for example, $ 1→2→4→5 $ .

In one second, you can perform one of the two following operations:

- Having a matryoshka $ a $ that isn't nested in any other matryoshka and a matryoshka $ b $ , such that $ b $ doesn't contain any other matryoshka and is not nested in any other matryoshka, you may put $ a $ in $ b $ ;
- Having a matryoshka $ a $ directly contained in matryoshka $ b $ , such that $ b $ is not nested in any other matryoshka, you may get $ a $ out of $ b $ .

According to the modern aesthetic norms the matryoshka dolls on display were assembled in a specific configuration, i.e. as several separate chains of nested matryoshkas, but the criminal, following the mysterious plan, took out all the dolls and assembled them into a single large chain ( $ 1→2→...→n $ ). In order to continue the investigation Andrewid needs to know in what minimum time it is possible to perform this action.

## 说明/提示

In the first sample test there are two chains: $ 1→2 $ and $ 3 $ . In one second you can nest the first chain into the second one and get $ 1→2→3 $ .

In the second sample test you need to disassemble all the three chains into individual matryoshkas in 2 + 1 + 1 = 4 seconds and then assemble one big chain in 6 seconds.

## 样例 #1

### 输入

```
3 2
2 1 2
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 3
3 1 3 7
2 2 5
2 4 6
```

### 输出

```
10
```

# 题解

## 作者：Qiancy1427 (赞：0)

### 题意理解

有 $n$ 个套娃，已经存在了 $k$ 个链。现在要求将所有套娃按顺序套成一个链，求最少步骤。

将套娃 $a$ 从 $b$ 中取出算一步，将 $b$ 套到 $a$ 上算一步。

### 解题思路

因为要套成一整列，那么起始的套娃编号一定是 $1$。所以其他所有的链都要拆开，每拆开一个长 $m$ 的链花费 $m-1$ 步。套娃 $1$ 所在链上的套娃分情况考虑，如果是编号对应的，保留不动；编号不对应的取下来，每取一个花费 $1$ 步。之后再将所有取下来的套娃套回去。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,a,ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>m>>a;
		if(a==1){	//套娃 1 所在的链 
			int cnt=1;
			for(int j=2;j<=m;j++){
				cin>>a;
				if(a==j)	cnt++;	//记录编号对应的套娃的数量 
			}
			ans+=m-cnt+n-cnt;	//分别为要取下的步骤和套上去的步骤 
		}
		else{
			for(int j=2;j<=m;j++)	cin>>a;
			ans+=m-1;	//剩最后一个套娃的时候就不算步数了 
		}
	}
	cout<<ans;
	return 0;
}
```

整体来说本题主要考察思维，但难度也不算很大，主要在于要想清要怎样取下和套上。个人认为属于较低难度的橙题。

---

## 作者：qjxqjx (赞：0)

## 题目大意：
现有 n 个套娃，大的能套在小的上面，已有 m 个链，最终需要按顺序套好，每次可以取下一个最上面的或把一个单独的套在一整个链上。求最小的步骤数。

## 题目思路：
除了第一个和最后一个套娃，其他的套娃都是上下都有一个套娃的，所以说：除了和 1 相连的有序的链以外，剩下的每个链上面的套娃都需要取下一次的再套上上一次的，最下面的只需要套一次。从而可得知：只需找出 $1,2,3……$ 已经排好的有几个套娃就行了。

## 代码：
```
#include<bits/stdc++.h>
#include<iostream>
//#include<cstdio>
#define manx 100005
using namespace std;
int n,k,f,cot=1,m,x,ans=0;
int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++){
        cin>>m>>f;
        if(f==1){
            for(int i=2;i<=m;i++){
                cin>>x;
                if(x==i){
                	cot++;
                }
            }
            ans+=m-cot;
        }else{
            for(int i=1;i<m;i++){
                cin>>x;
            }
            ans+=m-1;
        }
    }
    ans+=n-cot;
    cout<<ans;
    return 0;
}
```


---

