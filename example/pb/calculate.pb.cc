// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: calculate.proto

#include "calculate.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace zprpc {
PROTOBUF_CONSTEXPR CalcRequest::CalcRequest(
    ::_pbi::ConstantInitialized)
  : num1_(0)
  , num2_(0){}
struct CalcRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CalcRequestDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CalcRequestDefaultTypeInternal() {}
  union {
    CalcRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CalcRequestDefaultTypeInternal _CalcRequest_default_instance_;
PROTOBUF_CONSTEXPR CalcResponse::CalcResponse(
    ::_pbi::ConstantInitialized)
  : result_(0){}
struct CalcResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CalcResponseDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CalcResponseDefaultTypeInternal() {}
  union {
    CalcResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CalcResponseDefaultTypeInternal _CalcResponse_default_instance_;
}  // namespace zprpc
static ::_pb::Metadata file_level_metadata_calculate_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_calculate_2eproto = nullptr;
static const ::_pb::ServiceDescriptor* file_level_service_descriptors_calculate_2eproto[1];

const uint32_t TableStruct_calculate_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::zprpc::CalcRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::zprpc::CalcRequest, num1_),
  PROTOBUF_FIELD_OFFSET(::zprpc::CalcRequest, num2_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::zprpc::CalcResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::zprpc::CalcResponse, result_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::zprpc::CalcRequest)},
  { 8, -1, -1, sizeof(::zprpc::CalcResponse)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::zprpc::_CalcRequest_default_instance_._instance,
  &::zprpc::_CalcResponse_default_instance_._instance,
};

const char descriptor_table_protodef_calculate_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017calculate.proto\022\005zprpc\")\n\013CalcRequest\022"
  "\014\n\004num1\030\001 \001(\001\022\014\n\004num2\030\002 \001(\001\"\036\n\014CalcRespo"
  "nse\022\016\n\006result\030\001 \001(\0012r\n\013CalcService\022.\n\003Ad"
  "d\022\022.zprpc.CalcRequest\032\023.zprpc.CalcRespon"
  "se\0223\n\010Multiply\022\022.zprpc.CalcRequest\032\023.zpr"
  "pc.CalcResponseB\003\200\001\001b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_calculate_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_calculate_2eproto = {
    false, false, 228, descriptor_table_protodef_calculate_2eproto,
    "calculate.proto",
    &descriptor_table_calculate_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_calculate_2eproto::offsets,
    file_level_metadata_calculate_2eproto, file_level_enum_descriptors_calculate_2eproto,
    file_level_service_descriptors_calculate_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_calculate_2eproto_getter() {
  return &descriptor_table_calculate_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_calculate_2eproto(&descriptor_table_calculate_2eproto);
namespace zprpc {

// ===================================================================

class CalcRequest::_Internal {
 public:
};

CalcRequest::CalcRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:zprpc.CalcRequest)
}
CalcRequest::CalcRequest(const CalcRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&num1_, &from.num1_,
    static_cast<size_t>(reinterpret_cast<char*>(&num2_) -
    reinterpret_cast<char*>(&num1_)) + sizeof(num2_));
  // @@protoc_insertion_point(copy_constructor:zprpc.CalcRequest)
}

inline void CalcRequest::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&num1_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&num2_) -
    reinterpret_cast<char*>(&num1_)) + sizeof(num2_));
}

CalcRequest::~CalcRequest() {
  // @@protoc_insertion_point(destructor:zprpc.CalcRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CalcRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CalcRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void CalcRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:zprpc.CalcRequest)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&num1_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&num2_) -
      reinterpret_cast<char*>(&num1_)) + sizeof(num2_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CalcRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // double num1 = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 9)) {
          num1_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // double num2 = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 17)) {
          num2_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* CalcRequest::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:zprpc.CalcRequest)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // double num1 = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num1 = this->_internal_num1();
  uint64_t raw_num1;
  memcpy(&raw_num1, &tmp_num1, sizeof(tmp_num1));
  if (raw_num1 != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(1, this->_internal_num1(), target);
  }

  // double num2 = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num2 = this->_internal_num2();
  uint64_t raw_num2;
  memcpy(&raw_num2, &tmp_num2, sizeof(tmp_num2));
  if (raw_num2 != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(2, this->_internal_num2(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:zprpc.CalcRequest)
  return target;
}

size_t CalcRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:zprpc.CalcRequest)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double num1 = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num1 = this->_internal_num1();
  uint64_t raw_num1;
  memcpy(&raw_num1, &tmp_num1, sizeof(tmp_num1));
  if (raw_num1 != 0) {
    total_size += 1 + 8;
  }

  // double num2 = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num2 = this->_internal_num2();
  uint64_t raw_num2;
  memcpy(&raw_num2, &tmp_num2, sizeof(tmp_num2));
  if (raw_num2 != 0) {
    total_size += 1 + 8;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CalcRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    CalcRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CalcRequest::GetClassData() const { return &_class_data_; }

void CalcRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<CalcRequest *>(to)->MergeFrom(
      static_cast<const CalcRequest &>(from));
}


void CalcRequest::MergeFrom(const CalcRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:zprpc.CalcRequest)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num1 = from._internal_num1();
  uint64_t raw_num1;
  memcpy(&raw_num1, &tmp_num1, sizeof(tmp_num1));
  if (raw_num1 != 0) {
    _internal_set_num1(from._internal_num1());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_num2 = from._internal_num2();
  uint64_t raw_num2;
  memcpy(&raw_num2, &tmp_num2, sizeof(tmp_num2));
  if (raw_num2 != 0) {
    _internal_set_num2(from._internal_num2());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CalcRequest::CopyFrom(const CalcRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:zprpc.CalcRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CalcRequest::IsInitialized() const {
  return true;
}

void CalcRequest::InternalSwap(CalcRequest* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CalcRequest, num2_)
      + sizeof(CalcRequest::num2_)
      - PROTOBUF_FIELD_OFFSET(CalcRequest, num1_)>(
          reinterpret_cast<char*>(&num1_),
          reinterpret_cast<char*>(&other->num1_));
}

::PROTOBUF_NAMESPACE_ID::Metadata CalcRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_calculate_2eproto_getter, &descriptor_table_calculate_2eproto_once,
      file_level_metadata_calculate_2eproto[0]);
}

// ===================================================================

class CalcResponse::_Internal {
 public:
};

CalcResponse::CalcResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:zprpc.CalcResponse)
}
CalcResponse::CalcResponse(const CalcResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  result_ = from.result_;
  // @@protoc_insertion_point(copy_constructor:zprpc.CalcResponse)
}

inline void CalcResponse::SharedCtor() {
result_ = 0;
}

CalcResponse::~CalcResponse() {
  // @@protoc_insertion_point(destructor:zprpc.CalcResponse)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CalcResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void CalcResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void CalcResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:zprpc.CalcResponse)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  result_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CalcResponse::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // double result = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 9)) {
          result_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* CalcResponse::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:zprpc.CalcResponse)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // double result = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_result = this->_internal_result();
  uint64_t raw_result;
  memcpy(&raw_result, &tmp_result, sizeof(tmp_result));
  if (raw_result != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(1, this->_internal_result(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:zprpc.CalcResponse)
  return target;
}

size_t CalcResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:zprpc.CalcResponse)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double result = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_result = this->_internal_result();
  uint64_t raw_result;
  memcpy(&raw_result, &tmp_result, sizeof(tmp_result));
  if (raw_result != 0) {
    total_size += 1 + 8;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CalcResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    CalcResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CalcResponse::GetClassData() const { return &_class_data_; }

void CalcResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<CalcResponse *>(to)->MergeFrom(
      static_cast<const CalcResponse &>(from));
}


void CalcResponse::MergeFrom(const CalcResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:zprpc.CalcResponse)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_result = from._internal_result();
  uint64_t raw_result;
  memcpy(&raw_result, &tmp_result, sizeof(tmp_result));
  if (raw_result != 0) {
    _internal_set_result(from._internal_result());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CalcResponse::CopyFrom(const CalcResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:zprpc.CalcResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CalcResponse::IsInitialized() const {
  return true;
}

void CalcResponse::InternalSwap(CalcResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(result_, other->result_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CalcResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_calculate_2eproto_getter, &descriptor_table_calculate_2eproto_once,
      file_level_metadata_calculate_2eproto[1]);
}

// ===================================================================

CalcService::~CalcService() {}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* CalcService::descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_calculate_2eproto);
  return file_level_service_descriptors_calculate_2eproto[0];
}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* CalcService::GetDescriptor() {
  return descriptor();
}

void CalcService::Add(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                         const ::zprpc::CalcRequest*,
                         ::zprpc::CalcResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method Add() not implemented.");
  done->Run();
}

void CalcService::Multiply(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                         const ::zprpc::CalcRequest*,
                         ::zprpc::CalcResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method Multiply() not implemented.");
  done->Run();
}

void CalcService::CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                             ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                             const ::PROTOBUF_NAMESPACE_ID::Message* request,
                             ::PROTOBUF_NAMESPACE_ID::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), file_level_service_descriptors_calculate_2eproto[0]);
  switch(method->index()) {
    case 0:
      Add(controller,
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ::zprpc::CalcRequest*>(
                 request),
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<::zprpc::CalcResponse*>(
                 response),
             done);
      break;
    case 1:
      Multiply(controller,
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ::zprpc::CalcRequest*>(
                 request),
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<::zprpc::CalcResponse*>(
                 response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& CalcService::GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::zprpc::CalcRequest::default_instance();
    case 1:
      return ::zprpc::CalcRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& CalcService::GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::zprpc::CalcResponse::default_instance();
    case 1:
      return ::zprpc::CalcResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

CalcService_Stub::CalcService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
CalcService_Stub::CalcService_Stub(
    ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
    ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::PROTOBUF_NAMESPACE_ID::Service::STUB_OWNS_CHANNEL) {}
CalcService_Stub::~CalcService_Stub() {
  if (owns_channel_) delete channel_;
}

void CalcService_Stub::Add(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                              const ::zprpc::CalcRequest* request,
                              ::zprpc::CalcResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}
void CalcService_Stub::Multiply(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                              const ::zprpc::CalcRequest* request,
                              ::zprpc::CalcResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(1),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace zprpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::zprpc::CalcRequest*
Arena::CreateMaybeMessage< ::zprpc::CalcRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::zprpc::CalcRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::zprpc::CalcResponse*
Arena::CreateMaybeMessage< ::zprpc::CalcResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::zprpc::CalcResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>