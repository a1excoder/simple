package lambda1;

import java.util.Scanner;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class EmbededFuncs {
    public static void main(String[] args) {
        Predicate<String> predicate = x -> x.length() > 0;
        System.out.println(predicate.test(""));
        System.out.println(predicate.test("1"));
        System.out.println(predicate.test("Alex"));

        BinaryOperator<Integer> binaryOperator = (x, y) -> x * y;
        System.out.println(binaryOperator.apply(5, 5));

        Function<Double, String> from_double_to_string = x -> "Number is: " + String.valueOf(x);
        System.out.println(from_double_to_string.apply(44.3));

        Supplier<String> getString = ()->{
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter: ");
            return scanner.nextLine();
        };

        String string = getString.get();
        System.out.printf("string is: %s\n", string);
    }
}
