### Theory of compilers

#### Implementation of my own programming language

##### Code samples

```
test t = {
  title: 'My first test',
}

question q1 = {
  description: 'What's your name',
}

question q2 = {
  description: 'How old are you',
}

question q3 = {}

t->questions->add(q1)
t->questions->add(q2)
t->questions->add(q3)
t->questions->remove(q3)

<!-- t->questions->amount --> 2

t->answers->add({
  id: 1,
  q1: 'Vadim',
  q2: '21',
})

t->answers->add({
  id: 2,
  q1: 'Max',
  q2: '25',
})

forEach(question in t) {
  print(answer->q1)
}

forEach(answer in t) {
  print(answer->q1)
}
```
