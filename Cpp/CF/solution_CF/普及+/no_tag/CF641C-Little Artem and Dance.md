# Little Artem and Dance

## 题目描述

Little Artem is fond of dancing. Most of all dances Artem likes rueda — Cuban dance that is danced by pairs of boys and girls forming a circle and dancing together.

More detailed, there are $ n $ pairs of boys and girls standing in a circle. Initially, boy number $ 1 $ dances with a girl number $ 1 $ , boy number $ 2 $ dances with a girl number $ 2 $ and so on. Girls are numbered in the clockwise order. During the dance different moves are announced and all pairs perform this moves. While performing moves boys move along the circle, while girls always stay at their initial position. For the purpose of this problem we consider two different types of moves:

1. Value $ x $ and some direction are announced, and all boys move $ x $ positions in the corresponding direction.
2. Boys dancing with even-indexed girls swap positions with boys who are dancing with odd-indexed girls. That is the one who was dancing with the girl $ 1 $ swaps with the one who was dancing with the girl number $ 2 $ , while the one who was dancing with girl number $ 3 $ swaps with the one who was dancing with the girl number $ 4 $ and so one. It's guaranteed that $ n $ is even.

Your task is to determine the final position of each boy.

## 样例 #1

### 输入

```
6 3
1 2
2
1 2
```

### 输出

```
4 3 6 5 2 1
```

## 样例 #2

### 输入

```
2 3
1 1
2
1 -2
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 2
2
1 3
```

### 输出

```
1 4 3 2
```

# 题解

## 作者：AirQwQ (赞：2)

那道题想到的肯定是暴力，但是 $2\le n\le 10^6,1\le q\le 2  \times  10^6$，肯定不行。

那暴力不行怎么化简呢？

- 首先如果没有操作 $2$ 那很简单，统计出移动步数总和最后再计算即可。

- $2$ 的操作本质是奇偶互换，也可以理解为奇数加 $1$ 偶数减 $1$，但是奇数和奇数，偶数和偶数的**相对位置不变**。

所以得到方法：

1. 用 $odd_{plus}$ 记录奇数的移动步数，$even_{plus}$ 记录偶数移动步数。

2. 用 $odd_{flag}$ 记录奇数是否改变，$even_{plus}$ 记录偶数是否改变。(其实一个就够了，但两个更好理解）

3. 遇到操作 ```1 x``` 对 $odd_{plus}$ 和 $even_{plus}$ 加上 $x$，如果 $ x \equiv 1\pmod {2} $ 对 $odd_{flag}$ 和 $even_{flag}$ 进行改变即可。

4. 遇到操作 ```2``` 只需要对 $odd_{flag}$ 和 $even_{flag}$ 进行改变即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;
int odd_plus,even_plus;
bool odd_flag=1,even_flag;//odd_flag一定是1。
int ans[1000005];

int Move(int step){
	if(step%n) return (step+n)%n;
	return n;
}//和约瑟夫差不多的圆环处理方法。

signed main(){
    std::ios::sync_with_stdio(0);
    cin>>n>>q;
	while(q--){
        int flag;
		cin>>flag;
		if(flag==1){
			int move;
			cin>>move;
			even_plus=Move(even_plus+move); 
            _plus=Move(odd_plus+move);
			if(move&1) 
                odd_flag^=1,even_flag^=1;//利用位运算简写
		}
        else{
			if(even_flag) 
            	even_plus=Move(even_plus+1);
			else 
            	even_plus=Move(even_plus-1);
			if(odd_flag) 
            	odd_plus=Move(odd_plus+1);
			else 
            	odd_plus=Move(odd_plus-1);//如果奇偶性做处理
			odd_flag^=1,even_flag^=1;//加一减一也能最后处理
		}
	}
	for(int i=1;i<=n;++i)
		if(i&1) 
        	ans[Move(odd_plus+i)]=i;
		else 
        	ans[Move(even_plus+i)]=i;//不要去想第一个是多少，想第几个是一更方便。
	for(int i=1;i<=n;++i) 
        cout<<ans[i]<<' ';//其实也可以不用数组，直接输出，但太麻烦（我没做出来
	return 0;
}
```





---

## 作者：qian_shang (赞：1)

一道结论题

（~~才拿到这道题的时候觉得是个毒瘤数据结构，可能是因为我太弱了~~）

------------

观察题目，发现只有两种操作：

>1.整体往一个方向移动$x$个人  
>2.奇数偶数互相交换

这个时候就有一个~~显然~~的的结论产生了：

>_所有奇（偶）数的相对位置不变_ 

于是我们可以直接预处理奇(偶)数的变换规律

最后$O(n)$扫一遍修改就行了

注意一个小细节：

>每一次修改后要将位置变合法也就是将位置变为$1$到$n$

>可以写一个函数让它合法：

>```inline int moo(int A){return (A+n)%n==0?n:(A+n)%n;}```

详见代码注释：

```
#include<bits/stdc++.h>
#define R register
#define LL long long
#define N 1000005
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}//快读
int n,q,kind,x,y,v,jx,jy=1,ans[N];
inline int moo(int A){return (A+n)%n==0?n:(A+n)%n;}、
//找到合法的位置
int main(){
	n=read();q=read();
	while (q--){
		kind=read();
		if (kind==1){
			v=read(); v%=n;
			x=moo(x+v); y=moo(y+v);
			if (v&1) jx^=1,jy^=1;//如果加一个奇数会改变奇偶性
		}else {
			if (jx) x=moo(x+1);
				else x=moo(x-1);
			if (jy) y=moo(y+1);
				else y=moo(y-1);
			jx^=1,jy^=1;//交换肯定也要改变
        		 //考试的时候没加这一句，全WA,QAQ
		}
	}
	for (R int i=1;i<=n;i++){
		if (i&1) ans[moo(i+y)]=i;
			else ans[moo(i+x)]=i;
		//修改答案	
	}
	for (R int i=1;i<=n;i++) printf("%d ",ans[i]);//输出
	return 0;
}
```

题解有锅或有疑问的私信。。

---

## 作者：czh___ (赞：0)

### 思路
从第一组样例能发现虽然整体在变，但是相邻的两个数是始终在一起的，但是这并不是正解，因为当移动的位数是奇数的时候再经过奇偶互换就不挨着了。然后我随便造一个样例，发现不管怎么变奇偶性相同的相邻的数都是隔着一个数的顺序排列的，然后想一下变化过程的确是这样。于是我们只需要知道 $1$ 在哪就能找到所有奇数的位置，知道 $2$ 在哪就能找到所有偶数的位置，$1$ 和 $2$ 随便找就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1000001],a[1000001],n,q,a1,a2=1;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=0;i<q;i++){
        int op,len;
        scanf("%d",&op);
        if(op==1){
            scanf("%d",&len);
            a1=(a1+len+n)%n,
            a2=(a2+len+n)%n;
        }
        else{
            if((a1+1)&1) 
				a1++;
            else 
				a1--;
            if((a2+1)&1)
				a2++;
            else 
				a2--;
        }
    }
    ans[1]=a1,ans[2]=a2;
    a[a1]=1,a[a2]=2;
    for(int i=3;i<=n;i++)
        ans[i]=(ans[i-2]+2)%n,a[ans[i]]=i;
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}
```

[改编于](https://blog.csdn.net/Dreamon3/article/details/51277929?ops_request_misc=&request_id=&biz_id=102&utm_term=Little%20Artem%20and%20Dance&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-4-51277929.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：wang_freedom (赞：0)

### 思路：
简单操作题。

$2$ 的操作可理解为奇数加 $1$，偶数减 $1$，但奇偶之间相对位置不变。

可以对操作进行化简：

用 $odd_{plus}$ 记录奇数的移动步数，$even_{plus}$ 记录偶数移动步数。

用 $odd_{flag}$ 记录奇数是否改变，$even_{flag}$ 记录偶数是否改变。

遇到操作 1 x 对 $odd_{plus}$ 和 $even_{plus}$ 加上 $x$，如果 $x\equiv1\pmod2$ 对 $odd_{flag}$ 和 $even_{flag}$ 进行改变即可。

遇到操作 2 只需要对 $odd_{flag}$ 和 $even_{flag}$ 进行改变即可。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
#define pii pair<int,int>
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int n,q,odd_plus,even_plus,ans[1000005];
bool odd_flag=1,even_flag;
int Move(int step){
	if(step%n)
		return(step+n)%n;
	return n;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	while(q--){
        int op;
		cin>>op;
		if(op==1){
			int move;
			cin>>move;
			even_plus=Move(even_plus+move); 
            odd_plus=Move(odd_plus+move);
			if(move&1){
                odd_flag=!odd_flag;
				even_flag=!even_flag;
            }
		}
        else{
			if(even_flag) 
            	even_plus=Move(even_plus+1);
			else 
            	even_plus=Move(even_plus-1);
			if(odd_flag) 
            	odd_plus=Move(odd_plus+1);
			else 
            	odd_plus=Move(odd_plus-1);
			odd_flag^=1,even_flag^=1;
		}
	}
	rep(i,1,n)
		if(i&1)
        	ans[Move(odd_plus+i)]=i;
		else
        	ans[Move(even_plus+i)]=i;
	rep(i,1,n)
        cout<<ans[i]<<' ';
	return 0;
}
/*

*/

```

---

