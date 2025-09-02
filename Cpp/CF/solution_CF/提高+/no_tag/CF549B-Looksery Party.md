# Looksery Party

## 题目描述

Looksery 公司由  $n$  名员工所组成，每个员工都有自己的电话和联系人列表。

 最近，公司打算举办一场大型派对，每位到场的员工，都会向他的联系人发送消息，来说明这场派对有多炫酷。由于每个人都想花尽量多的时间来享受派对时光，他们会不假思索地向所有联系人发送消息，甚至包括他们自己。

 Looksery 公司的开发者 Igor 和 Max 就每个人收到了多少条消息展开了争论. Igor 钦点了  $n$  个数字，其中第  $i$  个数字表示 Igor 认为第  $i$  个人收到的消息条数。如果 Igor 猜到了至少  $1$  个数字就算他胜利，否则 Max 胜利。

 作为 Max 的支持者，你需要根据员工的联系人列表，确定是否存在 Igor 会输的情况。具体来说，你需要确定哪些人应该参加派对，使得派对结束后，任意一个人收到的消息条数与 Igor 所给出的不同。

## 样例 #1

### 输入

```
3
101
010
001
0 1 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
1
1
1
```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
1111
0101
1110
0001
1 0 1 0
```

### 输出

```
4
1 2 3 4 
```

# 题解

## 作者：Node_Edge (赞：6)

**简化题意：**

- 有 $n$ 个员工，如果有人参加派对，就会向所有他通讯录上的人发送一条消息。

- 询问是否存在一种参加派对的方案，使得对于第 $i$ 个人收到的信息的条数都不等于 $a_i$，如果无法构造，输出 $-1$。

注：每个人的通讯录中的都有他自己。

**思路**

1. 若不存在 $a_i=0$，则使所有人都不参加，结束。

2. 若 $a_i=0$，则第 $i$ 个人去，并把他发消息的人减一，再次查找是否存在 $a_i=0$，若不存在 $a_i=0$，则执行第 $1$ 步，否则继续执行第 $2$ 步

注：最坏情况下，所有人都能变成 $0$，这时 $n$ 个人参加派对，仍然满足，故不存在 $-1$ 的情况。

**核心代码**

```cpp
//s为所有员工的联系人列表，其他变量为题目所示
int find() {
	for (int i=1;i<= n;i++) {
		if (!a[i]){
            return i;
        } 
	}
	return 0; 
}
while(1){
    int flag=find();
    if(!flag){
        break;
    }
    ans[++m]=flag;
    for(int i=1;i<=n;++i){
        if(s[flag][i]=='1'){
            a[i]--;
        }
    }
}
```

---

## 作者：moye到碗里来 (赞：3)

贪心，每次找出收到信息为0的，必须去，由于题目保证有自己给自己发信息，所以去了之后这个点就一定满足了，更新，然后再做，做了n次发现还有等于0，说明必输，就这样，代码挺短的
```
#include<bits/stdc++.h>
using namespace std;
int n;
int cnt = 0;
int ans[105] = {0};
int num[104];
int to[105][105];
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			scanf("%1d",&to[i][j]);
		}
	}
	for(int i = 1; i <= n; ++i){
		scanf("%d",&num[i]);
	}
	int flag = 0;
	int t = 0;
	while(1){
		++t;flag = 0;
		for(int i = 1; i <= n; ++i){
			if(num[i] == 0 && ans[i] == 0){
				ans[i] = 1;
				cnt ++;
				for(int j = 1; j <= n; ++j){
					if(to[i][j] == 1)num[j] --;
				}
				flag = 1;
				break;
			}
		}
		if(flag == 0)break;
		if(t > n){printf("-1");return 0;}	
	}
	printf("%d\n",cnt);
	for(int i = 1; i <= n; ++i){
		if(ans[i] == 1){
			printf("%d ",i);
		}
	}
}
```

---

## 作者：Composite_Function (赞：0)

# 一、题意

给出 $n$ 个人及其他们的通讯录以及一个人所猜测的情况 $a_1,a_2,......,a_n$ ，每一个人只要参加了派对就会给通讯录上的人发消息。求有没有一种情况使得 $\forall 1 ≤ a ≤ n $ , 第 $i$ 个人收到的信息 ≠ $a_i$ ,若有，输出那些人；否则，输出 $-1$ 。

------------

# 二、思路

分为以下情况

1. 若 $\forall 1 ≤ a ≤ n $ 且第 $i$ 个人未参加, $a_i ≠ 0$ ，一个人都不参加即可，跳到情况 $3$ 。否则跳到情况 $2$ 。
2. 若 $a_i=0$ 因为会给自己也发信息，使第 $i$个人参加即可，跳到情况 $1$ 重新执行。
3. 成功，输出结果。

这时，你一定会想：咦？输出 $-1$ 的情况怎么没有呢？可以发现，最坏情况下所有人参加派对没有人还需判断，所以不存在输出 $-1$ 的情况。

------------

# 三、AC代码

```cpp
//讲解上面都有了，就不写注释了
//作者做了防抄处理哦
#include<bits/stdc++.h>
using namespace std；
#define N 110
int n,cnt；
bool ans[N]；
int num[N]；
char val[N][N]；
int main(){
    cin>>n;
    for(int i=1；i<=n；i++)
        for(int j=1；j<=n；j++)
            cin>>val[i][j]；
    for(int i=1；i<=n；i++)
        cin>>num[i]；
    bool flag=false； int t=0；
    while(true){
        t++,flag=false；
        for(int i=1；i<=n；i++)
            if(num[i]==0&&ans[i]==0){
                ans[i]=true,cnt？？/*到底怎么样自己好好想想哦*/;
                for(int j=1；j<=n；j++)
                    num[j]-=(val[i][j]=='1')；
                flag=true； break；
            }
        if(flag==false) break；
    }
    cout<<cnt<<endl;
    for(int i=1;i<=n;i++)
        if(ans[i]==true) cout<<i<<" "；
    return 0;
}
```

---

