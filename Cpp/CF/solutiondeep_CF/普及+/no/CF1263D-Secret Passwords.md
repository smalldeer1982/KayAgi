# 题目信息

# Secret Passwords

## 题目描述

One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of $ n $ passwords — strings, consists of small Latin letters.

Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords $ a $ and $ b $ as follows:

- two passwords $ a $ and $ b $ are equivalent if there is a letter, that exists in both $ a $ and $ b $ ;
- two passwords $ a $ and $ b $ are equivalent if there is a password $ c $ from the list, which is equivalent to both $ a $ and $ b $ .

If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.

For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:

- admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab";
- admin's password is "d", then you can access to system by using only "d".

Only one password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to guaranteed access to the system. Keep in mind that the hacker does not know which password is set in the system.

## 说明/提示

In the second example hacker need to use any of the passwords to access the system.

## 样例 #1

### 输入

```
4
a
b
ab
d
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
ab
bc
abc
```

### 输出

```
1```

## 样例 #3

### 输入

```
1
codeforces
```

### 输出

```
1```

# AI分析结果

### 题目内容（中文重写）
# 秘密密码

## 题目描述
有一个不知名的黑客想要获取AtForces测试系统的管理员密码，以获取下一场比赛的题目。为了实现这一目标，他潜入了管理员的办公室，偷走了一张写有 $n$ 个密码的纸条，这些密码均由小写拉丁字母组成。

黑客回到家后开始准备入侵AtForces。他发现系统中仅包含偷来的列表中的密码，并且系统判断密码 $a$ 和 $b$ 等价的规则如下：
- 若存在一个字母同时出现在 $a$ 和 $b$ 中，则密码 $a$ 和 $b$ 等价；
- 若列表中存在一个密码 $c$，它与 $a$ 和 $b$ 都等价，则密码 $a$ 和 $b$ 等价。

如果系统中设置了某个密码，而使用与之等价的密码尝试访问系统，用户将能够成功登录。

例如，如果列表中包含密码 "a"、"b"、"ab"、"d"，那么密码 "a"、"b"、"ab" 彼此等价，但密码 "d" 与列表中的其他任何密码都不等价。换句话说：
- 如果管理员的密码是 "b"，那么使用 "a"、"b"、"ab" 中的任何一个密码都可以登录系统；
- 如果管理员的密码是 "d"，那么只有使用 "d" 才能登录系统。

列表中只有一个密码是测试系统的管理员密码。请帮助黑客计算出为了确保能够登录系统所需的最少密码数量。请记住，黑客并不知道系统中设置的是哪个密码。

## 说明/提示
在第二个示例中，黑客只需使用列表中的任何一个密码就可以登录系统。

## 样例 #1
### 输入
```
4
a
b
ab
d
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
ab
bc
abc
```
### 输出
```
1
```

## 样例 #3
### 输入
```
1
codeforces
```
### 输出
```
1
```

### 算法分类
并查集

### 综合分析与结论
这些题解的核心思路都是利用并查集来解决密码等价类的合并问题，最终统计不同等价类的数量。不同题解在实现细节上有所差异，主要体现在合并的对象（是字符串还是字母）、合并的方式以及统计答案的时机等方面。

### 所选题解
- **作者：Meatherm（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接使用并查集合并出现相同字母的字符串，最后统计不同祖先的数量得到答案。
    - **核心代码**：
```cpp
int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}
inline void Union(int x,int y){
    int X=find(x),Y=find(y);
    if(X!=Y){
        f[X]=Y;
    }
    return;
}
// ...
for(rr int i=1;i<=n;++i){
    f[i]=i;
    scanf("%s",s);
    int len=strlen(s);
    for(rr int j=0;j<len;++j){
        a[s[j]-'a'+1].push_back(i);
    }
}
for(rr int i=1;i<=26;++i){
    int siz=a[i].size();
    for(rr int j=0;j<siz;++j){
        Union(a[i][j],a[i][0]);
    }
}
int cnt=0;
for(rr int i=1;i<=n;++i){
    if(f[i]==i)
        ++cnt;
}
```
- **作者：OldVagrant（4星）**
    - **关键亮点**：使用启发式合并优化并查集，通过维护集合大小和字符串数量，减少合并的复杂度。
    - **核心代码**：
```c
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return;
    if(size[x]<size[y]) swap(x,y);
    fa[y]=x,size[x]+=size[y],col[x]+=col[y],col[y]=0;
}
// ...
for(int i=1;i<27;i++) fa[i]=i,size[i]=1;
for(int i=1;i<=n;i++) read(i); 
for(int i=1;i<27;i++) if(col[i]) ans++;
```
- **作者：_GW_（4星）**
    - **关键亮点**：思路简洁，通过记录每个字母第一次出现的字符串位置，合并出现相同字母的字符串，最后统计连通块数量。
    - **核心代码**：
```cpp
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    int fax=find(x),fay=find(y);
    if(fax!=fay)
    {
        res++;
        fa[fax]=fay;
    }
}
// ...
for(int i=1;i<=n;i++)
{
    cin>>s;
    for(int j=0;j<s.size();j++)
    {
        if(mp[s[j]])
        {
            merge(mp[s[j]],i);
        }
        if(!mp[s[j]])
        {
            mp[s[j]]=i;
        }
    }
}
int res=0;
for(int i=1;i<=n;i++)
{
    if(fa[i]==i)
    {
        res++;
    }
}
```

### 最优关键思路或技巧
- **并查集的使用**：利用并查集的合并和查找操作，高效地处理密码之间的等价关系，将等价的密码合并到同一个集合中。
- **字母映射**：通过将字母映射到数组或集合中，方便统计每个字母在哪些字符串中出现，从而进行合并操作。
- **优化合并**：如启发式合并，优先将小的集合合并到大的集合中，减少树的高度，提高查找效率。

### 可拓展之处
同类型题或类似算法套路：
- 连通性问题：判断图中连通块的数量，如判断网络中不同子网的数量。
- 等价类划分：对具有等价关系的元素进行分类，如对相似的图像、文本进行分类。

### 推荐洛谷题目
- [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)
- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)
- [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)

### 个人心得摘录与总结
- **Zvelig1205**：提到要注意数组大小，不能只开到 $2\times10^5$，因为还有 $+26$，否则可能需要调试一段时间，提醒我们在实现代码时要仔细考虑数组的边界和范围。
- **Karry5307**：感慨自己无缘 Expert，说明算法水平的提升需要慢慢积累，鼓励大家持续学习和练习。 

---
处理用时：53.59秒