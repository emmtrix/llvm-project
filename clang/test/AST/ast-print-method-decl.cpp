// RUN: %clang_cc1 -ast-print %s -o - -std=c++20 | FileCheck %s

// CHECK: struct DelegatingCtor1 {
struct DelegatingCtor1 {
  // CHECK-NEXT: DelegatingCtor1();
  DelegatingCtor1();

  // CHECK-NEXT: DelegatingCtor1(int) : DelegatingCtor1() {
  DelegatingCtor1(int) : DelegatingCtor1() {
    // CHECK-NEXT: }
  }

  // CHECK-NEXT: };
};


// CHECK: struct DelegatingCtor2 {
struct DelegatingCtor2 {
  // CHECK-NEXT: template <typename Ty> DelegatingCtor2(Ty);
  template <typename Ty> DelegatingCtor2(Ty);

  // FIXME: Implicitly specialized method should not be output
  // CHECK-NEXT: template<> DelegatingCtor2<float>(float);

  // CHECK-NEXT: DelegatingCtor2(int X) : DelegatingCtor2((float)X) {
  DelegatingCtor2(int X) : DelegatingCtor2((float)X) {
  // CHECK-NEXT: }
  }

  // CHECK-NEXT: };
};

// CHECK: struct DelegatingCtor3 {
struct DelegatingCtor3 {
  // FIXME: template <> should not be output
  // CHECK: template <> DelegatingCtor3(auto);
  DelegatingCtor3(auto);

  // FIXME: Implicitly specialized method should not be output
  // CHECK: template<> DelegatingCtor3<const char *>(const char *);

  // CHECK: DelegatingCtor3(int) : DelegatingCtor3("") {
  DelegatingCtor3(int) : DelegatingCtor3("") {
  // CHECK-NEXT: }
  }

  // CHECK-NEXT: };
};

// CHECK: struct CurlyCtorInit {
struct CurlyCtorInit {
  // CHECK-NEXT: struct A {
  struct A {
  // CHECK-NEXT: };
  };

  // CHECK-NEXT: A a1;
  A a1;
  // CHECK-NEXT: A a2;
  A a2;
  // CHECK-NEXT: int b;
  int b;

  // CHECK-NEXT: CurlyCtorInit() : a1({}), a2{}, b{} {
  CurlyCtorInit() : a1({}), a2{}, b{} {
  // CHECK-NEXT: }
  }

  // CHECK-NEXT: };
};

