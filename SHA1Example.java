import java.security.*;

public class SHA1Example {
    public static void main(String[] args) throws Exception {
        String input = "Hello, World!";
        MessageDigest md = MessageDigest.getInstance("SHA-1");
        byte[] hash = md.digest(input.getBytes());

        StringBuilder hexString = new StringBuilder();
        for (byte b : hash) hexString.append(String.format("%02x", b));

        System.out.println("SHA-1 Hash: " + hexString.toString());
    }
}