# 题目信息

# Exam

## 题目描述

An exam for $ n $ students will take place in a long and narrow room, so the students will sit in a line in some order. The teacher suspects that students with adjacent numbers ( $ i $ and $ i+1 $ ) always studied side by side and became friends and if they take an exam sitting next to each other, they will help each other for sure.

Your task is to choose the maximum number of students and make such an arrangement of students in the room that no two students with adjacent numbers sit side by side.

## 样例 #1

### 输入

```
6```

### 输出

```
6
1 5 3 6 2 4```

## 样例 #2

### 输入

```
3
```

### 输出

```
2
1 3```

# AI分析结果

### 题目翻译
# 考试

## 题目描述
有 $n$ 名学生将在一个又长又窄的房间里参加考试，所以学生们将按某种顺序排成一排就座。老师怀疑编号相邻（$i$ 和 $i + 1$）的学生总是坐在一起学习并成为了朋友，如果他们在考试时相邻而坐，肯定会互相帮助。

你的任务是选择最多数量的学生，并安排这些学生在房间里就座，使得没有两个编号相邻的学生坐在一起。

## 样例 #1
### 输入
```
6
```
### 输出
```
6
1 5 3 6 2 4
```

## 样例 #2
### 输入
```
3
```
### 输出
```
2
1 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先对一些特殊的 $n$ 值（如 $n \leq 4$）进行特判，因为这些情况无法用通用方法处理，然后对于 $n > 4$ 的情况，通过一定的规律来构造满足条件的学生排列。大部分题解采用先输出奇数再输出偶数的方式，部分题解采用了其他构造方式。

### 所选的题解
- **作者：Aw顿顿 (赞：7)，4星**
    - **关键亮点**：思路清晰，对特判情况和通用情况都有详细的分析和证明，代码可读性高。
    - **个人心得**：提到随机打乱判断的方法不靠谱且易超时，引导思考更合适的方法。
- **作者：LucasXu80 (赞：2)，3星**
    - **关键亮点**：提供了 Python 代码，思路较为清晰，对可能出现的错误有一定的分析。
- **作者：LittleSnowy (赞：0)，3星**
    - **关键亮点**：给出了另一种构造方式的思路和代码，有一定的创新性。

### 重点代码
#### Aw顿顿的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n<=2){
        puts("1\n1");
        return 0;
    }
    if(n==3){
        puts("2\n1 3");
        return 0;
    }
    if(n==4){
        puts("4\n3 1 4 2");
        return 0;
    }
    cout<<n<<endl;
    for(int i=1;i<=n;i+=2)cout<<i<<' ';
    for(int i=2;i<=n;i+=2)cout<<i<<' ';
    return 0;
}
```
**核心实现思想**：先对 $n \leq 4$ 的情况进行特判，输出对应的结果。对于 $n > 4$ 的情况，先输出所有奇数，再输出所有偶数。

#### LucasXu80 的代码
```python
n=int(input())
if n==2: 
    print(1)
    print(1)
elif n==3:
    print(2)
    print("1 3")
elif n==4:
    print(4)
    print("2 4 1 3")
else:
    print(n)
    for i in range(1,n+1,2): print(i,end=' ')
    for i in range(2,n+1,2): print(i,end=' ')
```
**核心实现思想**：同样先对 $n = 2, 3, 4$ 的情况进行特判，对于其他情况，先输出 $n$，再依次输出所有奇数和偶数。

#### LittleSnowy 的代码
```cpp
#include<stdio.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n<=2)printf("1\n1");
	if(n==3)printf("2\n1 3");
	if(n>3)
	{
		printf("%d\n",n);
		for(int i=1;i<=n/2;i++)printf("%d %d ",i+n/2,i);
		if(n%2==1)printf("%d",n);
	}
return 0;
}
```
**核心实现思想**：先对 $n \leq 3$ 的情况进行特判，对于 $n > 3$ 的情况，若 $n$ 为偶数，按照 $i + n/2$ 和 $i$ 的顺序输出；若 $n$ 为奇数，将 $1$ 到 $n - 1$ 按偶数情况输出，最后补上 $n$。

### 最优关键思路或技巧
- 先对小范围的 $n$ 值进行特判，因为这些情况可能不满足通用规律。
- 对于 $n > 4$ 的情况，采用奇偶分开输出的方式构造满足条件的排列，这样可以保证相邻学生编号差不为 $1$。

### 拓展思路
同类型题可能会有其他的构造要求，比如要求排列满足其他特定条件，或者在不同的场景下进行构造。类似算法套路可以是先分析特殊情况，再寻找通用的构造方法。

### 推荐洛谷题目
- P1008 三连击
- P1012 拼数
- P1036 选数

---
处理用时：28.36秒