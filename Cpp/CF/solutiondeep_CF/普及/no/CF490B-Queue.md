# 题目信息

# Queue

## 题目描述

During the lunch break all $ n $ Berland State University students lined up in the food court. However, it turned out that the food court, too, has a lunch break and it temporarily stopped working.

Standing in a queue that isn't being served is so boring! So, each of the students wrote down the number of the student ID of the student that stands in line directly in front of him, and the student that stands in line directly behind him. If no one stands before or after a student (that is, he is the first one or the last one), then he writes down number 0 instead (in Berland State University student IDs are numerated from $ 1 $ ).

After that, all the students went about their business. When they returned, they found out that restoring the queue is not such an easy task.

Help the students to restore the state of the queue by the numbers of the student ID's of their neighbors in the queue.

## 说明/提示

The picture illustrates the queue for the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF490B/08daf79334436a27cb8cf554f27be1c975002c35.png)

## 样例 #1

### 输入

```
4
92 31
0 7
31 0
7 141
```

### 输出

```
92 7 31 141 
```

# AI分析结果



# Queue 队列恢复

## 题目描述
午餐时间，所有 $n$ 个伯兰州立大学学生在美食广场排成一队。由于餐厅临时午休暂停服务，学生们记录了队列中前一个和后一个同学的学号（若没有则记为0）。现需根据这些记录恢复原始队列顺序。

## 输入格式
输入包含 $n+1$ 行：
- 首行为整数 $n$
- 后续 $n$ 行每行两个整数，表示每个学生记录的前后学号

## 输出格式
输出恢复后的队列顺序。

## 样例输入
```
4
92 31
0 7  
31 0
7 141
```

## 样例输出
`92 7 31 141`

## 算法分类
构造、链表

---

## 精选题解分析

### 题解1：Edmundino（★★★★☆）
**核心思路**：
1. **首尾特征**：队列首元素的前驱出现次数为1，末元素的后继出现次数为1
2. **链表映射**：建立前驱到后继的映射表`lat[]`
3. **分奇偶填充**：
   - 偶数位从`lat[0]`开始遍历（样例中的7）
   - 奇数位通过出现次数特征找到首元素后遍历

**关键代码**：
```cpp
void jie(int o,int x) { // 链表遍历函数
    while(o>0) {
        ans[x]=o;
        x=x+2;
        o=lat[o];
    }
}
```

### 题解2：Y_QWQ_Y（★★★★★）
**优化亮点**：
1. **双向链表**：使用`nxt[]`和`pre[]`数组记录前后关系
2. **首尾定位**：通过`pre[i]==-1`直接定位队首
3. **同步遍历**：交替填充奇偶位置，空间利用率更优

**核心实现**：
```cpp
int i=0, j=2; // 偶数位起点
while(nxt[i]) {
    ans[j] = nxt[i];
    i = nxt[i];
    j += 2;
}

int rt; // 奇数位起点
for(i=1;i<=N;i++) if(pre[i]==-1 && v[i]) {rt=i; break;}

j=1; // 奇数位填充
while(rt) {
    ans[j] = rt;
    rt = nxt[rt];
    j += 2;
}
```

---

## 最优策略总结
1. **链表特征识别**：利用首尾元素在记录中的唯一性特征
2. **分治处理**：将队列拆分为奇偶两个子序列分别处理
3. **空间换时间**：使用大数组直接建立学号映射（学号范围已知时）
4. **边界处理**：正确处理0的特殊情况，避免死循环

## 拓展应用
适用于需要重建链式结构的场景，如：
1. 二叉树中序遍历恢复
2. 图论中的欧拉路径查找
3. 基因组序列拼接

---

## 推荐练习题
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列应用
2. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449) - 序列结构解析
3. [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996) - 循环链表模拟

---
处理用时：51.66秒