/*

Q1. Implement set with integers in range {1…N}, implements five operations, add, remove, 
contains, clear, iterate. 

v1: using only bucket array with size N+1, the operation costs are:     O(1),O(1), O(1),  O(N), O(N)    for example: if we add, 2, 0, 1, it will become list:[1, 1, 1]
v2: using only sequential array(store them sequentially in array):      O(1),O(count),O(count),O(1),  O(count)for example: if we add, 2, 0, 1, it will become map: [2, 0, 1] you need to keep an count
v3: achieve best of v1 and v2’s performance:                            O(1),O(1), O(1), O(1), O(count)

Note: I was thinking similar to LRU, using array + linkedlist. So that would make add, remove, contains and iterates optimal. 
But it doesn’t handle clear with O(1).  The right answer is to use the two array given. For bucket array value, 
it will be the index in the sequential array. The sequential array value will be the actually value. in the above example it 
will become list:[1, 2, 0], map[2, 0, 1]
A couple of things to notice: 
1) how to remove? remove will not shift the rest of the array front, instead, it will pick the map[toRemove] = map[count - 1]; count—; 
2) how to clear: map just need to set count to 0. 
3) after clear, because we don’t clear list, how do we know if the list pointer to the map are invalidate or not(this will affect contains and add)? 
    there are two things to consider, 
    #1. if list[x] >= count - 1, then it is definitely invalid; 
    #2 if list[x] < count but it still possible that it’s replaced by other element(e.g. add 2, clear, add 1, 
    now list[2] and list[1] both points to map[0]). So you should also check if map[list[x]] == x.

Q: Multi thread question: Event class has two methods, void register(Callback cb); void fire(); it should run like this:

Event e = new Event();
e.register(cb1);// Not invoke until event is fired.
e.register(cb2);// Same
...
e.fire(); // cb1.invoke(); cb2.invoke();
...
e.register(cb3); // cb3.invoke() right away since event has been fired.

Implement the two methods in both single-thread and multi-thread scenario with mutex;
Single thread:

boolean isFired = false;
Queue<Callback> q = new Queue<Callback>();

void register(Callback cb) {
  if (!isFired) {
    q.enqueue(cb);
  } else {
    cb.invoke();
  }
}

void fire() {
  while(!q.isEmpty()) {
    Callback cb = q.dequeue();
    cb.invoke();
  }

  isFired = true;
}

// if this is used in multi-thread condition, there are a couple of problems: 1) if say register finished if check(isFired = false) and then fire is run and finished(isFired = true), then cb in register is left in the queue without anyone running. Our next iteration can be:
boolean isFired = false;
Queue<Callback> q = new Queue<Callback>();
Mutex m = new Mutex();
void register(Callback cb) {
  m.acquire();
  if (!isFired) {
    q.enqueue(cb);
  } else {
    cb.invoke();
  }
  m.release();
}

void fire() {
  m.acquire();
  while(!q.isEmpty()) {
    Callback cb = q.dequeue();
    cb.invoke();
  }

  isFired = true;
  m.release();
}

// This is good. it will protect the atomicity. But it is slow because invoke could take a long time. But, if we change register to below it won’t work because fire() can be called after if (isFired) check and before m.acquire(); cb is left in the queue again.

Mutex m = new Mutex();
void register(Callback cb) {
  if (!isFired) {
    m.acquire();
    q.enqueue(cb);
    m.release();
  } else {
    cb.invoke();
  }

}

// Next iteration on register. The reason we put m.release() before cb.invoke() is because invoke() we have no control and it could call this.register again and because Mutex is not reentrant we are going to have a deadlock and b) invoke can take a long time which make everything slower.

void register(Callback cb) {
  m.acquire();
  if (!isFired) {
    q.enqueue(cb);
    m.release();
  } else {
    m.release();
    cb.invoke();
  }

}

// Now this looks good. We move on to fire(). Same as register, non-reentrant mutex can cause problem again with invoke(). So we should move invoke() outside.
void fire() {
  m.acquire();
  while(!q.isEmpty()) {
    Callback cb = q.dequeue();
    m.release();
    cb.invoke();
    m.acquire();
  }

  isFired = true;
  m.release();
}

// Summary: exclude invoke() since we have no control; keep boolean isFired consistent with q status(q.isEmpty()), which is achieved by the last acquire and release.

// Q: Happy Number
// Next(xyz) = x^2 + y^2 + z^2. 
// 7 -> 49 (16+81) -> 97(81+49) -> 130(1+9) -> 10 -> 1:: Happy Number
// We might end up with either of the three cases 
// 1. Finally get down to 1, Happy Number
// 2. Enter a cycled patten, Unhappy Number
// 3. It grows infinitely large, which is not possible 
//    999999(6*81) 
// O(logbn), O(logn)
*/

int GetNext( int n )
{
    int sum = 0;
    while ( n )
    {
        sum += (n%10) * (n%10);
        n /= 10;
    }
    
    return sum;
}

bool isHappy(int n) {
    unordered_set<int> NumSeen;
    while ( n != 1 && NumSeen.count(n) == 0 )
    {
        NumSeen.insert(n);
        n = GetNext(n);
    }
    if ( n == 1 )
        return true;
    return false;
}

// We can also use the Floyd cycle detection method which leverges two pointers
bool isHappy(int n) {
    int slow = n;
    int fast = GetNext(n);
    while ( slow != 1 && slow != fast )
    {
        slow = GetNext(slow);
        fast = GetNext(GetNext(fast));
    }
    
    if ( slow == 1 )
        return true;
    return false;
    
}