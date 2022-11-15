#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dataexchange/DataExchangeClient.h>
#include <aws/dataexchange/model/SendApiAssetRequest.h>

int main(int argc, char** argv)
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    {
        Aws::DataExchange::DataExchangeClient client;
	const char* data_set_id = "8d494cba5e4720e5f6072e280daf70a8";
	const char* revision_id = "32559097c7d209b02af6de5cad4385fe";
	const char* asset_id = "4e94198cfdb8400793fb3f0411861960";

	const char* path = "/";
	const char* method = "POST";
	const char* body = "{\"body_param\": \"body_param_value\"}";
	const std::shared_ptr<Aws::IOStream> body_stream = Aws::MakeShared<Aws::StringStream>(body);
	Aws::Map<Aws::String, Aws::String> request_headers;
	Aws::Map<Aws::String, Aws::String> query_string_parameters;

        Aws::DataExchange::Model::SendApiAssetRequest send_api_asset_request;

	request_headers.insert(std::make_pair<Aws::String, Aws::String>("Content-Type", "application/json"));

	query_string_parameters.insert(std::make_pair<Aws::String, Aws::String>("param1", "value1"));
	query_string_parameters.insert(std::make_pair<Aws::String, Aws::String>("param2", "value2"));

	send_api_asset_request
	    .WithDataSetId(data_set_id)
	    .WithRevisionId(revision_id)
	    .WithAssetId(asset_id)
	    .WithPath(path)
	    .WithMethod(method)
	    .WithRequestHeaders(request_headers);

	send_api_asset_request.SetBody(body_stream);

        auto outcome = client.SendApiAsset(send_api_asset_request);

        if (outcome.IsSuccess()) {
	    auto response_headers = outcome.GetResult().GetResponseHeaders();

	    std::cout << "Response Headers:\n\n";
	    for (auto const &response_header: response_headers) {
                std::cout << "\t" << std::get<0>(response_header) << " = " << std::get<1>(response_header) << "\n";
            }
	    std::cout << "\nResponse Body:\n\n";
	    std::cout << outcome.GetResult().GetBody().rdbuf() << std::endl;
        } else {
            std::cerr << "SendApiAsset error: "
                << outcome.GetError().GetExceptionName() << " - "
                << outcome.GetError().GetMessage() << std::endl;
        }
    }

    Aws::ShutdownAPI(options);
}
