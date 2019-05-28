# Vector

## Užduoties tikslas

Sukurti std:vector pakaitalą.

## 5 funkcijos

### Insert
```c++
iterator insert (iterator position, const value_type& val) {
        size_type index = position-begin();

        if (avail == limit)
            grow();

        iterator pos = &data[index];

        std::move(pos, avail++, pos+1);

        *pos = val;


        return &data[0];
}
```

### Resize

```c++
 void resize(size_type size, value_type val = {}) {

        unsigned int currSize = this->size();

        if (size == currSize) {
            return;
        }

        iterator new_data = alloc.allocate(size);

        iterator new_avail = std::copy(data, data+size, new_data);

        if (size > currSize) {
            std::uninitialized_fill(new_data+currSize, new_avail, val);
        }

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = new_avail;
}
```    

### Erase

```c++
iterator erase(iterator it) {

      if (it > avail) {
          throw std::out_of_range("Out of range");
      }

      std::move(it + 1, avail--, it);

      return it;

}
```
```c++
void erase (iterator first, iterator last) {
  if (first > avail || last > avail) {
      throw std::out_of_range("Out of range");
  }
  size_type range = last - first;

  std::move(last+1, avail, first);

  avail -= (range+1);
}
```

### Reserve

```c++
void reserve(size_type size) {
        if (size <= capacity()) {
            return;
        }

         iterator new_data = alloc.allocate(size);
         iterator new_avail = std::uninitialized_copy(data, avail, new_data);

         uncreate();

         data = new_data;
         avail = new_avail;
         limit = data + size;
}
```    

### Shrink To Fit

```c++
void shrink_to_fit() {

        if (limit == avail) {
            return;
        }

        iterator it = limit;
        while (it != avail) {
            alloc.destroy(--it);
        }

        alloc.deallocate(avail, limit - avail);

        limit = avail;
}
```    

## Spartos analizė

### Skaičių įrašymas į std::vector ( šis skaičiavimas yra main.cpp faile )

```
Testuojame std::vector
------------------------------------------------

10000 skaiciu:
10000 skaiciu irasymas uztruko 0.000992
Perskirstymas buvo atliktas 14 kartu
100000 skaiciu:
100000 skaiciu irasymas uztruko 0.002976
Perskirstymas buvo atliktas 31 kartu
1000000 skaiciu:
1000000 skaiciu irasymas uztruko 0.023808
Perskirstymas buvo atliktas 51 kartu
10000000 skaiciu:
10000000 skaiciu irasymas uztruko 0.24392
Perskirstymas buvo atliktas 75 kartu
100000000 skaiciu:
100000000 skaiciu irasymas uztruko 2.28604
Perskirstymas buvo atliktas 102 kartu
```

### Skaičių įrašymas į Vector ( šis skaičiavimas yra main.cpp faile )

```
Testuojame Vector
------------------------------------------------

10000 skaiciu:
10000 skaiciu irasymas uztruko 0.000992
Perskirstymas buvo atliktas 14 kartu
100000 skaiciu:
100000 skaiciu irasymas uztruko 0.002976
Perskirstymas buvo atliktas 31 kartu
1000000 skaiciu:
1000000 skaiciu irasymas uztruko 0.026286
Perskirstymas buvo atliktas 51 kartu
10000000 skaiciu:
10000000 skaiciu irasymas uztruko 0.280736
Perskirstymas buvo atliktas 75 kartu
100000000 skaiciu:
100000000 skaiciu irasymas uztruko 2.57126
Perskirstymas buvo atliktas 102 kartu
```

### Studentų įrašymas į std::vector 

```
Testuojame 10 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.001982
Irasymas ivykdytas per 0.006973

Testuojame 100 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.001489
Irasymas ivykdytas per 0.010019

Testuojame 1000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.012365
Irasymas ivykdytas per 0.047619

Testuojame 10000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.134433
Irasymas ivykdytas per 0.646788

Testuojame 100000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 1.88827
Irasymas ivykdytas per 8.85261

Testavimas baigtas

```

### Studentų įrašymas į Vector

```
Testuojame 10 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0
Irasymas ivykdytas per 0.009424

Testuojame 100 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.001551
Irasymas ivykdytas per 0.010029

Testuojame 1000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.014908
Irasymas ivykdytas per 0.061009

Testuojame 10000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 0.158209
Irasymas ivykdytas per 0.822863

Testuojame 100000 studentu  atskyrima kai kiekvienas studentas turi po 5 pazymius:
Operacija su Vector ivykdyta per 1.36896
Irasymas ivykdytas per 7.39137

Testavimas baigtas
```
    
    
