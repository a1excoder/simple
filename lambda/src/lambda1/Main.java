package lambda1;

public class Main {
    public static void main(String[] args) {
        Math<Integer> sum = Integer::sum;
        Math<Double> minus = (a, b)->a-b;
        Math<Integer> multiply = (a, b)->a*b;
        Math<Integer> divide = (a, b)->{
            if (b == 0) return 0; // throw new Exception()
            return a / b;
        };

        System.out.println(sum.calculate(12, 8));
        System.out.println(minus.calculate(12.3, 8.3));
        System.out.println(multiply.calculate(12, 8));
        System.out.println(divide.calculate(12, 0));

        DoMath(multiply, '*', 13, 6, 3, 64);
        DoMath((a, b) -> {
            if (b == 0) return 0;
            return a / b;
        }, '/', 200, 8, 5);
        DoMath(sum, '+', 12, 4);
        DoMath(minus, '-', 55.0, 15.0);


        math(Test::sum, 12, 8);

        TestInf math_t = Test::minus;
        math(math_t, 12, 8);

        Test test = new Test();
        math(test::multiply, 5, 25);


        UserBuilder builder = User::new;
        User user = builder.build("Alex");
        System.out.println(user.name());

        for (int i = 0; i <= 3; i++) {
            System.out.println(operation(i).DoMath(12, 8));
        }
    }

    @SafeVarargs
    private static <T>void DoMath(Math<T> func, char c, T... data) {
        T result = data[0];

        for (int i = 1; i < data.length; i++) {
            System.out.printf("%s %c %s = %s\n", result, c, data[i], (result = func.calculate(result, data[i])));
        }

    }

    public static void math(TestInf math_func, int a, int b) {
        System.out.printf("%d and %d = %d\n", a, b, math_func.DoMath(a, b));
    }

    private static TestInf operation(int type) {
        switch (type) {
            case 1: return (a, b) -> a + b;
            case 2: return (a, b) -> a - b;
            case 3: return (a, b) -> a * b;
            default: return (a, b) -> 0;
        }
    }
}

interface Math<T> {
    T calculate(T a, T b);
}

interface TestInf {
    int DoMath(int a, int b);
}

class Test {
    public static int sum(int a, int b) {
        return a + b;
    }

    public static int minus(int a, int b) {
        return a - b;
    }

    public int multiply(int a, int b) {
        return a * b;
    }
}