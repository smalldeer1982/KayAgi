# 题目信息

# [CEOI 1999] Parity Game

## 题目描述

Alice 和 Bob 在玩一个游戏：他写一个由 $0$ 和 $1$ 组成的序列。Alice 选其中的一段（比如第 $3$ 位到第 $5$ 位），问他这段里面有奇数个 $1$ 还是偶数个 $1$。Bob 回答你的问题，然后 Alice 继续问。Alice 要检查 Bob 的答案，指出在 Bob 的第几个回答一定有问题。有问题的意思就是存在一个 $01$ 序列满足这个回答前的所有回答，而且不存在序列满足这个回答前的所有回答及这个回答。

## 说明/提示

对于 $100\%$ 的数据，$1 \le  n \leq 10^9$，$m \leq 5 \times 10^3$。

## 样例 #1

### 输入

```
10
5
1 2 even
3 4 odd
5 6 even
1 6 even
7 10 odd```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何判断Alice询问Bob关于01序列区间奇偶性回答的正确性展开，大多采用并查集相关算法，并结合离散化处理大数据范围问题。思路上，先将区间奇偶性问题转化为前缀和的奇偶关系，再利用并查集的传递性维护这些关系。解决难点在于处理数据范围大以及维护奇偶性的传递关系。

### 所选的题解
- **作者：houzhiyuan（5星）**
    - **关键亮点**：思路清晰，先介绍所需知识点，再逐步分析做法，对种类并查集和离散化的讲解详细，代码注释丰富，可读性强。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
int zuxian(int k){//并查集函数，注意路径压缩
    return f[k]==k?k:f[k]=zuxian(f[k]);
}
void hebing(int x,int y){//合并函数
    int x1=zuxian(x);
    int x2=zuxian(y);
    if(x1!=x2){
        f[x1]=x2;
    }
}
// 主函数中处理离散化、并查集合并及判断矛盾的代码逻辑清晰
for(int i=1; i<=m; i++) {
    a[i].x=lower_bound(b+1,b+l+1,a[i].x)-b;//离散化
    a[i].y=lower_bound(b+1,b+l+1,a[i].y)-b;
    if(a[i].z==0){//种类并查集，分相同和不同操作
        if(zuxian(a[i].x)==zuxian(a[i].y+l)){//如果两个数奇偶性不同，矛盾，输出
            cout<<i-1;
            return 0;
        }
        else{//不然就合并集合
            hebing(a[i].x,a[i].y);
            hebing(a[i].x+l,a[i].y+l);
        }
    }
    else{
        if(zuxian(a[i].x)==zuxian(a[i].y)){//同理
            cout<<i-1;
            return 0;
        }
        else{
            hebing(a[i].x,a[i].y+l);
            hebing(a[i].x+l,a[i].y);
        }
    }
}
```
    - **核心实现思想**：通过`zuxian`函数查找并查集的祖先，实现路径压缩优化。`hebing`函数用于合并两个元素所在集合。在主函数中，先对输入数据离散化，然后根据区间奇偶性判断条件，利用并查集合并操作维护元素间的奇偶关系，若发现矛盾则输出当前回答的前一个序号。
- **作者：Eleven谦（4星）**
    - **关键亮点**：提供两种解法（种类并查集和带权并查集），对每种解法以问答形式详细阐述思路，代码简洁明了，对离散化也有清晰说明。
    - **个人心得**：初看想不到并查集，第二遍才读懂题。
    - **核心代码片段（种类并查集）**：
```cpp
inline int find(int x) {
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main() {
    scanf("%d%d",&n,&m);
    // 读入数据并离散化
    for(register int i=1;i<=m;i++) {
        scanf("%d%d",&a[i].u,&a[i].v);
        cin>>a[i].op;
        b[++tot]=a[i].u;
        b[++tot]=a[i].v;
    }
    sort(b+1,b+1+tot);
    res=unique(b+1,b+1+tot)-(b+1);
    for(register int i=1;i<=m;i++) {  
        a[i].u=lower_bound(b+1,b+1+res,a[i].u-1)-b;
        a[i].v=lower_bound(b+1,b+1+res,a[i].v)-b;
    } 
    for(register int i=1;i<=2*res;i++) fa[i]=i;
    // 根据回答进行并查集操作
    for(register int i=1;i<=m;i++) {
        if(a[i].op=="even") {  
            if(find(a[i].u)==find(a[i].v+res)||find(a[i].u+res)==find(a[i].v)) {  
                printf("%d",i-1);  
                return 0;
            }
            fa[find(a[i].u)]=find(a[i].v);
            fa[find(a[i].u+res)]=find(a[i].v+res);
        }
        else {
            if(find(a[i].u)==find(a[i].v)||find(a[i].u+res)==find(a[i].v+res)) {
                printf("%d",i-1);
                return 0;
            }
            fa[find(a[i].u)]=find(a[i].v+res);
            fa[find(a[i].u+res)]=find(a[i].v);
        }
    }
    printf("%d",m);
    return 0;
} 
```
    - **核心实现思想**：`find`函数查找元素祖先，实现路径压缩。主函数中先读入数据，通过排序、`unique`和`lower_bound`完成离散化。之后依据回答是“even”还是“odd”，在并查集中判断是否矛盾，若不矛盾则进行相应的合并操作。
- **作者：mot1ve（4星）**
    - **关键亮点**：从思维角度出发，先分析如何想到用并查集，再详细阐述扩展域并查集的思路，对传递和约束条件分析透彻，代码风格良好。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
int find(int x)
{
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void unionn(int x,int y)
{
    fa[find(x)]=find(y);
}
// 主函数中离散化及并查集操作
for(int i=1;i<=m;i++)
{
    a[i].x=lower_bound(b+1,b+1+cnt,a[i].x)-b;
    a[i].y=lower_bound(b+1,b+1+cnt,a[i].y)-b;
}
for(int i=1;i<=m;i++)//离散化完了，开始正常操作
{
    if(a[i].op=="even")
    {
        if(find(a[i].x)==find(find(a[i].y+cnt)))
        {
            printf("%d",i-1);
            return 0;
        }
        else
        {
            unionn(a[i].x,a[i].y);
            unionn(a[i].x+cnt,a[i].y+cnt);
        }
    }
    else
    {
        if(find(a[i].x)==find(a[i].y))
        {
            printf("%d",i-1);
            return 0;
        }
        else
        {
            unionn(a[i].x,a[i].y+cnt);
            unionn(a[i].x+cnt,a[i].y);
        }
    }
}
```
    - **核心实现思想**：`find`函数查找祖先，`unionn`函数合并集合。主函数先对数据离散化，然后根据区间奇偶性回答，在并查集中判断是否存在矛盾，若不存在则按规则合并集合。

### 最优关键思路或技巧
将区间奇偶性问题转化为前缀和的奇偶关系，利用并查集维护这种关系。通过扩展域并查集（将每个元素拆分为两个，分别表示奇偶性相同和不同的集合）或带权并查集（用边权表示奇偶关系）来处理奇偶性的传递性。同时，针对大数据范围采用离散化技巧，将实际用到的少量数据映射到较小范围。

### 可拓展之处
同类型题常考察对具有传递关系的条件判断，类似算法套路是先分析题目中的传递关系，然后选择合适的并查集类型（普通并查集、扩展域并查集、带权并查集等）进行维护。例如在涉及元素分组、关系判断等场景中都可能用到。

### 相似知识点题目推荐
- **P1196 [NOI2002]银河英雄传说**：通过并查集维护舰队之间的关系，涉及到并查集的合并与查找操作。
- **P1525 [NOIP2010 提高组] 关押罪犯**：利用扩展域并查集解决二分图判定问题，判断是否能将罪犯合理分配到两个监狱。
- **P2024 [NOI2001]食物链**：经典的扩展域并查集题目，维护三种不同关系（同类、捕食、被捕食），与本题维护奇偶两种关系类似。

### 个人心得摘录与总结
Eleven谦提到初看想不到并查集，第二遍才读懂题。这表明对于一些复杂问题，需要仔细分析题目条件和隐藏的逻辑关系，不能仅从表面理解。在面对难题时，可能需要多次阅读题目，挖掘潜在信息，才能找到合适的解题方法。 

---
处理用时：45.04秒