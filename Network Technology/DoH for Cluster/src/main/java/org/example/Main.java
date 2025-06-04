package org.example;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import java.security.cert.X509Certificate;

public class Main {
    public static void main(String[] args) {
        try {
            TrustManager[] trustAllCerts = new TrustManager[]{
                    new X509TrustManager() {
                        public X509Certificate[] getAcceptedIssuers() { return null; }
                        public void checkClientTrusted(X509Certificate[] certs, String authType) {}
                        public void checkServerTrusted(X509Certificate[] certs, String authType) {}
                    }
            };

            SSLContext sslContext = SSLContext.getInstance("TLS");
            sslContext.init(null, trustAllCerts, new java.security.SecureRandom());

            HttpClient client = HttpClient.newBuilder()
                    .sslContext(sslContext)
                    .build();

            String dohUrl = "https://192.168.222.227/dns-query";
            String domainName = "example.com";
            int recordType = 1; // A record

            URI uri = URI.create(dohUrl + "?name=" + domainName + "&type=" + recordType);

            HttpRequest request = HttpRequest.newBuilder()
                    .uri(uri)
                    .header("Accept", "application/dns-json")
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("HTTP Status: " + response.statusCode());
            System.out.println("Content-Type: " + response.headers().firstValue("Content-Type").orElse("unknown"));
            System.out.println("Response body:\n" + response.body());

            String contentType = response.headers().firstValue("Content-Type").orElse("");
            if (!contentType.contains("json")) {
                throw new RuntimeException("Server returned non-JSON response. Content-Type: " + contentType);
            }

            ObjectMapper objectMapper = new ObjectMapper();
            JsonNode jsonNode = objectMapper.readTree(response.body());

            if (jsonNode.has("Status") && jsonNode.get("Status").asInt() == 0) {
                if (jsonNode.has("Answer")) {
                    JsonNode answerArray = jsonNode.get("Answer");
                    for (JsonNode answer : answerArray) {
                        if (answer.has("type") && answer.get("type").asInt() == 1 && answer.has("data")) {
                            String ipAddress = answer.get("data").asText();
                            System.out.println("IP address: " + ipAddress);
                        }
                    }
                } else {
                    System.out.println("No DNS records found");
                }
            } else {
                String errorMsg = jsonNode.has("Comment") ? jsonNode.get("Comment").asText() : "Unknown error";
                System.err.println("DNS error (Status: " + jsonNode.get("Status").asInt() + "): " + errorMsg);
            }

        } catch (javax.net.ssl.SSLHandshakeException e) {
            System.err.println("SSL Handshake failed: " + e.getMessage());
            System.err.println("Check SSL Server Certificate");
        } catch (java.net.ConnectException e) {
            System.err.println("Connection failed: " + e.getMessage());
            System.err.println("Check the availability of the DNS server: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Error occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }
}